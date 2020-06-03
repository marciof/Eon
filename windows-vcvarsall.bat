@rem Batch file to invoke cmd.exe and avoid quoting issues, as well as to
@rem source and setup the build environment (eg. for Travis CI).

@rem Use an environment variable to choose the architecture since `shift`
@rem doesn't modify `%*`.
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" %VCVARSALL_ARCH%

%*
