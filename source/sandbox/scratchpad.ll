declare i8 * @malloc (i32)

define i8 * @malloc_wrapper (i32 %size)
{
    %result = call i8* @malloc (i32 %size)
    ret i8 * %result
}