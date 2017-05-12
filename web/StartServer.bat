set OUTPUTDIR=output
set STYLEDIR=style
START /B livereload %OUTPUTDIR%
START /B http-server %OUTPUTDIR%
START /B sass --watch %STYLEDIR%/main.scss:%OUTPUTDIR%/%STYLEDIR%/main-compiled.css
