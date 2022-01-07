
// 将项目转换为模板
/*
    虚幻引擎的模板为项目提供了一个强大的起点。可以使用它们快速开始针对特定平台的开发或创建专门
    的项目，例如多显示器体验。
    使用虚幻引擎，您还可以从现在创建自定义模板以满足您的特定需求。
    自定义模板是一个虚幻引擎项目，配置为引擎将其包含在创建新项目时出现的模板列表中。
    自定义模板可以包括内容，设置和代码，并且可以默认启用或禁用特定插件。

    步骤
    要将现有项目转换为模板：
        1.将整个项目的文件夹复制到Templates您的虚幻引擎安装文件夹中。如果您从Epic Games Launcher
        安装了Unreal Engine，则该Templates文件夹将位于：
            C:\Program Files\Epic Games\UE_[version]\Templates在Windows上
            /Users/Shared/Epic Games/UE_[version]/Templates在Mac上
        如果您从源代码编译虚幻引擎，则该Templates文件夹将位于[ForkLocation]\UE4\Templates。

        2.打开[ProjectName]\Config\DefaultGame.ini file.然后，添加或更新ProjectName变量。这是
        在创建新的虚幻引擎项目时将显示在模板选择屏幕中的名称。
        例子：
            [/Script/EngineSettings.GeneralProjectSettings]
            ProjectID=E6468D0243A591234122E38F92DB28F4
            ProjectName=MyTestTemplate
        请注意，ProjectID变量是为每个项目生成的唯一ID。

        3.从虚幻引擎安装文件夹中，转到Templates\TP_FirstPerson\Config\.将TemplateDefs.ini文件
        复制到[ProjectName]\Config文件夹中。
            可以使用任何现有的模板文件夹而不是TP_FirstPerson，只要它有一个TemplateDefs.ini文件。

        4.打开TemplateDefs.ini在上一步中复制的文件并更新LocalizedDisplayNames和LocalizedDescriptions
        变量。有四组变量，对应于虚幻引擎支持的每种语言：英语(en)、韩语(ko)、日语(ja)和简体中文(zh-Hans)。
        例子：
            [/Script/GameProjectGeneration.TemplateProjectDefs]
            LocalizedDisplayName=(Language="en",Text="My Test Template")
            LocalizedDescriptions=(Language="en",Text="This is a custom template that includes 
            a first-person character and uses Blueprint.")

        5.创建新项目时，模板将出现在TemplateDefs.ini文件中指定的类别中。这是由Categories变量控制的。
        尽管有变量名称，但模板只能分配一个类别。
        可能的选项是：
            游戏-游戏
            ME-电影、电视和现场活动
            AEC-建筑、工程和施工
            MFG-汽车、产品设计和制造
        有关详细信息，请打开TemplateCategories.ini [UE installation path]\UE_[vesion]\Templates
        文件夹中的文件。

        6.可以在[ProjectName]\Media文件夹中添加图标和预览图像。这些图像必须使用PNG格式并遵循以下命名
        约定：
            图标：[ProjectName].png。
            预览：[ProjectName]_Previes.png。

    最终结果
        现在应该在“新建项目”对话框中看到新模板。
        NOTE
            要查看新模板，您只需关闭并打开“新建项目”窗口。但是，如果对现有模板进行任何更改（例如，如果更
            改其名称或描述），则必须重新启动虚幻引擎，更改才会显示在此窗口中。
*/