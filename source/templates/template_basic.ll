
; Returns true, if %str1 and %str2 point to strings that are equal
define i1 @string_equals (i8 * %str1, i8 * %str2)
{
entry:
    ; Return true if %str1 points to the same string as %str2
    %same_strings = icmp eq i8 * %str1, %str2
    br i1 %same_strings, label %return_true, label %continue

continue:
    ; We need str1 and str2 on the stack to be able to increment them
    %local_str1 = alloca i8 *
    %local_str2 = alloca i8 *
    store i8* %str1, i8 ** %local_str1
    store i8* %str2, i8 ** %local_str2
    br label %start_while

start_while:
    
    ; Start while
    ; Get current character of str1 and str2 and compare them to 0
    ; Load the pointer values of %local_str1 and %local_str2
    %str1_current = load i8 ** %local_str1
    %str2_current = load i8 ** %local_str2
    ; Load the values the pointers point to
    %str1char = load i8 * %str1_current
    %str2char = load i8 * %str2_current
    
    ; Check whether the characters differ
    %str_differ = icmp ne i8 %str1char, %str2char
    br i1 %str_differ, label %return_false, label %continue_check

continue_check:
    ; Check whether %local_str1 is pointing to a null terminator
    %str1_at_end = icmp eq i8 %str1char, 0
    ; Check whether %local_str1 is pointing to a null terminator
    %str2_at_end = icmp eq i8 %str2char, 0
    ; When %local_str1 points to a null terminator, select whether %local_str2 is pointing to a null terminator, otherwise false
    %both_at_end = select i1 %str1_at_end, i1 %str2_at_end, i1 false
    ; Here %both_at_end is either true, because %str2_at_end was true, or false because %str1_at_end or %str2_at_end are false
    
    ; Before checking the result, increment %str1_current and store it to %local_str1
    %local_str1i = ptrtoint i8 * %str1_current to i32
    %local_str1inc = add i32 %local_str1i, 1
    %local_str1incptr = inttoptr i32 %local_str1inc to i8 *
    store i8 * %local_str1incptr, i8 ** %local_str1

    ; Do the same for %str2_current and %local_str2
    %local_str2i = ptrtoint i8 * %str2_current to i32
    %local_str2inc = add i32 %local_str2i, 1
    %local_str2incptr = inttoptr i32 %local_str2inc to i8 *
    store i8 * %local_str2incptr, i8 ** %local_str2

    ; Return true if they are both at end, since they did not differ, yet
    br i1 %both_at_end, label %return_true, label %start_while
    
return_true:
    ret i1 true

return_false:
    ret i1 false
}

declare i32 @printf(i8* noalias nocapture, ...)
declare i32 @scanf(i8* noalias nocapture, ...)

@.str_type_exit = private unnamed_addr constant [20 x i8] c"Type exit to quit.\0A\00"
@.str_input_mask = private unnamed_addr constant [3 x i8] c"%s\00"
@.str_newline = private unnamed_addr constant [2 x i8] c"\0a\00"
@.str_printmask_int = private unnamed_addr constant [3 x i8] c"%d\00"
@.str_exit_keyword = private unnamed_addr constant [5 x i8] c"exit\00"
@.str_printf_faculty = private unnamed_addr constant [13 x i8] c"Faculty: %d\0a\00"

define void @template_basic()
{
    %str_printmask_int  = getelementptr [3 x i8]* @.str_printmask_int, i32 0, i32 0
    %str_exit_keyword   = getelementptr [5 x i8]* @.str_exit_keyword, i32 0, i32 0
    %str_input_mask     = getelementptr [3 x i8]* @.str_input_mask, i32 0, i32 0
    %str_newline        = getelementptr [2 x i8]* @.str_newline, i32 0, i32 0
    %str_printf_faculty = getelementptr [13 x i8]* @.str_printf_faculty, i32 0, i32 0
    br label %start

start:
    ; initialized local variable:
    %faculty_start.addr = alloca i32;
    store i32 5, i32 * %faculty_start.addr
    %faculty_start = load i32 * %faculty_start.addr
    %faculty = load i32 * %faculty_start.addr
    %faculty.addr = alloca i32
    store i32 %faculty, i32* %faculty.addr
    %i.addr = alloca i32
    store i32 %faculty_start, i32* %i.addr
    br label %for.start

for.start:
    %i.15 = load i32* %i.addr
    %i_mod_2 = srem i32 %i.15, 2
    %i_mod_2_is_zero = icmp eq i32 %i_mod_2, 0
    br i1 %i_mod_2_is_zero, label %faculty_mul, label %faculty_add

faculty_mul:
    %faculty.1 = load i32* %faculty.addr    
    %i.1 = load i32* %i.addr
    %faculty.2 = mul i32 %faculty.1, %i.1
    store i32 %faculty, i32* %faculty.addr
    call i32 (i8*, ...)* @printf(i8* %str_printf_faculty, i32 %faculty.2)
    br label %switch.check_1

faculty_add:
    %faculty.3 = load i32* %faculty.addr
    %i.2 = load i32* %i.addr
    %faculty.4 = add i32 %faculty.3, %i.2
    store i32 %faculty, i32* %faculty.addr
    %faculty.5 = load i32* %faculty.addr
    call i32 (i8*, ...)* @printf(i8* %str_printf_faculty, i32 %faculty.5)
    br label %switch.check_1

switch.check_1:
    %i.6 = load i32* %i.addr
    %i.is_1 = icmp eq i32 %i.6, 1
    br i1 %i.is_1, label %switch.1, label %switch.check_2

switch.1:
    %i.7 = load i32 * %i.addr
    %i.8 = mul i32 %i.7, 2
    %faculty.7 = load i32 * %faculty.addr
    %faculty.8 = add i32 %faculty.7, %i.8
    store i32 %faculty.8, i32*  %faculty.addr
    br label %for.check_break

switch.check_2:
    %i.11 = load i32* %i.addr
    %i.is_2 = icmp eq i32 %i.11, 2
    br i1 %i.is_2, label %switch.2, label %switch.check_3

switch.2:
    %i.9 = load i32 * %i.addr
    %i.10 = mul i32 %i.9, 3
    %faculty.9 = load i32 * %faculty.addr
    %faculty.10 = sub i32 %faculty.9, %i.10
    store i32 %faculty.10, i32*  %faculty.addr
    br label %for.check_break

switch.check_3:
    %i.12 = load i32* %i.addr
    %i.is_3 = icmp eq i32 %i.12, 3
    br i1 %i.is_3, label %switch.3, label %for.check_break

switch.3:
    %i.13 = load i32 * %i.addr
    %i.14 = mul i32 %i.12, 3
    %faculty.12 = load i32 * %faculty.addr
    %faculty.13 = sub i32 %faculty.12, %i.14
    store i32 %faculty.13, i32*  %faculty.addr
    br label %for.check_break

for.check_break:
    %i.3 = load i32* %i.addr
    %i_is_zero = icmp eq i32 %i.3, 0
    br i1 %i_is_zero, label %for.exit, label %for.increment_and_continue

for.increment_and_continue:
    %i.4 = load i32* %i.addr
    %i.5 = sub i32 %i.4, 1
    store i32 %i.5, i32* %i.addr
    br label %for.start

for.exit:
    %faculty.6 = load i32* %faculty.addr
    call i32 (i8*, ...)* @printf(i8* %str_printf_faculty, i32 %faculty.6)

    %input_buffer = alloca [256 x i8]
    %input_buffer_begin = getelementptr [256 x i8] * %input_buffer, i32 0, i32 0
    call i32 (i8*, ...)* @scanf(i8* %str_input_mask, i8* %input_buffer_begin)
    %exit_input = call i1 @string_equals (i8* %input_buffer_begin, i8* %str_exit_keyword);
    br i1 %exit_input, label %exit, label %start

exit:
    ret void
}

define i32 @test()
{
    %result = add i32 10, 9
    ret i32 %result
}

define i32 @main_()
{
    call void @template_basic ()
    ret i32 0
}