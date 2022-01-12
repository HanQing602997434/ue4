
// 创建游戏模块
/*
    1.所需设置
        创建C++项目，如果是蓝图项目，添加C++代码转换为C++项目

    2.设置目录
        在Source目录下创建ModuleTest文件夹，创建Private和Public文件夹

    3.创建Build.cs文件
        当Unreal Build Tool(UBT)在项目目录中查找依赖项时，会忽略IDE解决方案文件，
        而是查看Source文件夹中的Build.cs**文件。每个模块都必须有一个'Build'.cs文
        件，否则UBT不会发现它。

        要设置您的Build.cs文件，请按照下列步骤操作：
            1.在模块的根目录创建一个名为ModuleTest.Build.cs文件。打开此文件并添加
            以下代码：
                using UnrealBuildTool;

                public class ModuleTest : ModuleRules
                {
                    public ModuleTest(ReadOnlyTargetRules Target) : base(Target)
                    {
                        
                    }
                }

            2.编辑构造函数，使其如下所示：
                public ModuleTest(ReadOnlyTargetRules Target) : base(Target)
                {
                    PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
                }

    4.用C++实现你的模块
        虽然Build.cs文件使UBT可以发现您的模块，模块还需要实现为C++类，以便引擎可以
        加载和卸载它。

        幸运的是，虚幻引擎包含可以为大多数常见实现简化此过程的宏。要制作快速实施文件，
        请按照下列步骤操作：
            1.导航到模块的根目录并打开Private文件夹。创建ModuleTestModule.cpp新文
            件。

            2.在ModuleTestModule.cpp里面，添加以下代码：
                #include "Modules/ModuleManage.h"
                
                IMPLEMENT_MODULE(FDefaultModuleImpl, ModuleTest);

            这为模块提供了一个默认实现，使其可用于C++代码。
            可以通过手动编写模块的类、它的构造函数以及它的启动和关闭函数来创建更详细
            的实现。对于大多数游戏模块，此默认实现足以加载和卸载模块。

    5.编译模块
        在定义和实现模块之后，编译的过程非常简单。
            1.右键单机MyProject.uproject并单击Generate Visual Studio Files以重新
            生成您的IDE解决方案。
            这样确保新模块在IDE和虚幻编辑器中可见。
            NOTE:
                每当重新组织模块的代码或更改Build.cs文件的内容时，都应该重新生成IDE
                解决方案以确保它保持最新。

            2.在Visual Studio中编译项目。新模块将一起编译。
            任何时候手动添加新模块、更改模块的目录结构、移动或重命名C++文件或更改模块
            的依赖项时，都应重新生成项目文件以更新Visual Studio解决方案，然后再次编译
            项目。
            NOTE:
                虽然可以在虚幻编辑器运行时编译项目，但有时需要关闭虚幻编辑器，然后在编
                译后重新启动以使重大更改或新类生效。

    6.在项目中包含模块
        模块应该能够编译，但要在项目中使用模块中的任何代码，需要将其注册到.uproject文件。
        1.打开MyProject根目录，然后MyProject.uproject在文本编辑器中打开并编辑"模块"列
        表，如下所示：
            "Modules": [
                {
                    "Name": "MyProject",
                    "Type": "Runtime",
                    "LoadingPhase": "Default"
                },
                {
                    "Name": "ModuleTest",
                    "Type": "Runtime"
                }
            ]
        可以使用此列表条目来配置它将加载的加载阶段及其类型。
        相比之下，编辑器模块只能在编辑器中运行。它还使用默认加载阶段，该阶段在加载游戏
        模块后进行初始化。

        2.导航到MyProject/Source文件夹，然后打开MyProject.Build.cs文件。添加ModuleTest
        到PublicDependencyModuleNames列表中。
            PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "ModuleTest"});

    7.向模块添加代码
        可以手动将C++文件添加到模块中的Public和Private目录，也可以在虚幻编辑器中添加
        它们。

        这些步骤将知道使用新建类向导将代码添加到模块：
            1.在虚幻编辑器中打开项目。
            2.在内容流浪其中，单机Add，然后单机New C++ Class。
            3.选择Actor作为父类，然后单机Next。
            4.找到名称字段旁边的下拉列表。它应该默认读取MyProject(Runtime)。单击此下
            拉列表，然后将其更改为ModuleTest(Runtime)。
            5.将类命名为ModuleActorBase，将Class Type设置为Public，然后单机Create Class.
            6.打开ModuleActorBase.cpp，然后将以下行添加到AModuleActorBase::BeginPlay
            函数中：
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, TEXT("Hello, world!"))
            7.保存代码编译模块。

    8.从模块中扩展代码
        最后，按照以下步骤测试新Actor类和主要游戏模块查看它的功能。
            1.在虚幻编辑器中打开项目。创建一个New Blueprint Class，然后展开All Classes列表。
            2.选择ModuleActorBase作为父类。将蓝图类命名为ModuleActorBP。
            3.将ModuleActorBP的副本从内容流浪其中拖到游戏世界中，单击播放按钮。
        如果在类聊表没有看到ModuleActorBase，请确保它的标题在Public文件夹，具有说明
        BlueprintType UCLASS符，并且已将ModuleTest模块添加到项目的依赖项中。
*/