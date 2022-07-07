
// 专用服务器
/*
    1.下载对应版本的源码，需要绑定Epic Games账号和Github
        例如当前是4.26.2版本：
            1).下载4.26版本的源码压缩包
            2).管理员运行Setup.bat文件，自动下载文件，大概40G左右
            3).管理员运行GenerateProjectFiles.bat生成sln工程
            4).用VS2017以上版本打开解决方案，用Development Editor Win64编译
            5).首次编译过程中会遇到各种问题，有可能是编译顺序导致，重新编译即可
            6).编译Development Server Win64

    2.设置服务器构建目标，添加一个可执行文件ProjectServer.exe
        1).打开项目解决方案
*/