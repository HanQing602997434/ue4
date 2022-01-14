
// 虚幻引擎模块
/*
    模块是虚幻引擎软件架构的基本构建块。它们将特定的编辑器工具、运行时特性、库或
    其他功能封装在独立的代码单元中。
    默认情况下，所有项目和插件都有自己的主模块，但是，可以在这些模块之外定义其他
    模块来组织代码。

    使用模块的好处
        使用模块组织项目具有以下的好处：
            1.模块强制执行良好的代码分离，提供封装功能和隐藏代码内部部分的方法。

            2.模块被编译为单独的编译单元。这意味着只有已更改的模块才需要编译，
            并且大型项目的构建时间将大大加快。

            3.根据Include What You Use(IWYU)标准，模块在依赖关系图中链接在一
            起，并且限制标头包含到实际使用的代码。这意味着项目中未使用的模块将
            被安全地排除在编译之外。

            4.可以控制在运行时加载和卸载特定模块的时间。这提供了一种通过管理哪
            些系统可用或活动来优化项目性能的方法。

            5.可以根据某些条件(例如正在为哪个平台编译项目)从项目中包含或排除模
            块。
        总而言之，遵循模块的最佳实践，项目代码将比将所有项目代码放入单个模块中
        时组织得更好，编译效率更高，并且可重用性更高。

    设置模块
        如何从头开始构建和实现模块。按照这些步骤，将创建一个独立于项目默认包含
        的主要模块的游戏模块。
            1.在项目的Source文件夹的顶层为模块创建一个目录。这个目录应该和模块
            同名。
                TIP
                    可以将模块放置在Source文件夹内的任何子目录中，深度任意多。
                    这使得使用子目录对模块进行分组称为可能。
            2.在模块的根目录中创建一个[ModuleName].Build.cs文件，并使用它来定
            义与其他模块的依赖关系。这使得Unreal构建系统能够发现模块。

            3.在模块的根目录中创建Private和Public子文件夹。

            4.在Private子文件夹中创建模块的[ModuleName]Module.cpp文件。使用它
            来提供启动和关闭模块的方法，以及虚幻引擎用来管理模块的其他常用功能。

            5.要控制模块加载的方式和时间，将模块的配置信息添加到.uproject或.uplugin
            文件。这包括模块的名称、类型、兼容平台和加载阶段。

            6.将模块列为Build.cs需要使用它的任何模块的文件中的依赖项。这可能包括
            Build.cs项目的主要模块的文件。

            7.当修改[ModuleName].Build.cs文件或在文件啊加之间移动源文件时，都会
            为IDE生成解决方案文件。可以使用以下任何一种方法来执行此操作：
                a.运行GenerateProjectFiles.bat。
                b.右键单击.uproject项目的文件，然后单击Generate Project Files。
                c.在虚幻编辑器中，单击文件>刷新Visual Studio项目。

    了解模块的结构
        所有模块都应该放在插件或项目的Source目录中。模块的根文件夹应与相应模块同名。
        每个模块的根文件夹应该有一个[ModuleName].Build.cs文件，其C++代码应该包含在
        Private和Public文件夹中。

        以下是推荐的模块文件夹结构示例：
            [ModuleName]
                Private
                    [ModuleName]Module.cpp
                    所有.cpp文件和私有标头
                Public
                    所有公共标头
                [ModuleName].Build.cs

    在Build.cs文件中配置依赖项
        Unreal构建系统根据Target.cs项目中的Build.cs文件和模块中的文件来构建项目，而
        不是根据IDE的解决方案文件。

        编辑代码时会自动生成IDE解决方案，但Unreal Build Tool(UBT)在编译项目时会忽略
        它。

        所有模块都需要[ModuleName].Build.cs放置在模块根目录中的文件，以便虚幻构建系
        统识别它们。

        在[ModuleName].Build.cs文件中，需要将模块定义为从ModuleRules类继承的类。
           using UnrealBuildTool;

           public class ModuleTest : ModuleRules
           {
               public ModuleTest(ReadOnlyTargetRules Target) : base(Target)
               {
                   PrivateDependencyModuleNames.AddRange(new string[] {"Core"});
               }
           }
        配置Build.cs文件时，将主要使用PrivateDependencyModuleName和PublicDependencyModuleNames
        列表。将模块名称添加到这些列表将设置可用于模块代码的模块。
        
        例如，将"Slate"和"SlateUI"模块名称添加到私有依赖项列表中，将能够在模块中包含Slate UI类。

    私有和公共依赖
        PublicDependencyModuleNames如果公开使用模块中的类，例如在公共.h文件中，则应该使用该列表。
        这将使依赖于模块的其他模块可以毫无问题地包含头文件。
        PrivateDependencyModuleNames如果模块仅用于私人用途，例如在.cpp文件中，则应将模块的名称放
        在列表中。尽可能首选私有依赖项，因为可以减少项目的编译时间。
            TIP
                可以通过在头文件中使用前向声明将许多依赖项设为私有而不是公开。
*/