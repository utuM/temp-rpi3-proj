#ifndef __GLOBAL_EXIT_CODE_HPP
#define __GLOBAL_EXIT_CODE_HPP

class ExitCode
{
public:
    /// 
    static const int skNoError = 0;

    ///
    static const int skErrCannotStartSocket = -1000;
    ///
    static const int skErrCannotStopSocket  = -1001;
};

#endif // #ifndef __GLOBAL_EXIT_CODE_HPP