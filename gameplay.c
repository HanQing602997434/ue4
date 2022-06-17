
// GamePlay框架
/*
    Actor-演员/个体
        组成世界的单位个体
        可相互嵌套
        组件的容器
        Spawn & Tick
        网络通信的通道
        派生出各种不同职责的Actor

    Component-组件
        组件是种能力
        为Actor提供能力
        能力一般与业务逻辑无关
        能力是跨游戏的

    ALevelScriptActor-关卡蓝图
        一个特殊的默认脚本Actor:ALevelScriptActor
        正经项目-大部分情况都不适合
        适合Demo，新手村
        适合一些关卡本身的触发机械互动

    APawn
        可被控制
        逻辑足够复杂MVC
        肉体
        人形角色

    AController & APlayerState
        用来控制别的Actor的Actor
        灵魂

        肉体状态
        抽离开是为了联机复制

    APlayerController & AAIController
        主角灵魂
        和玩家沟通的渠道

        AI灵魂
        行为树功能强大
        黑板共享数据
        AI感知
        EQS环境查询

    ULevel关卡
        Actor的集合
        World里的板块
        对应umap

    UWorld
        Level的集合
        运行时的真正的Actor集合
        “关卡”的真正单位
        场景的真正表示对象

    AGameMode & AGameState
        世界规则
        最权威

        世界状态
        通知到各端

    UGameInstance - USaveGame
        整场游戏的全局实例
        World的外围管理对象
        跨关卡的逻辑

        游戏存档

    USubsystem
        业务逻辑的组件
        5个生命周期粒度控制
        自动生成对象
        托管生命周期
        替代Manager类
*/

// 实战架构
/*
    玩家登录DS server会在GameMode中进行登录退出
        登录：OnPostLogin，登录在每次切换关卡时会进行
        退出：OnLogout，退出在退出关卡时会进行

    在GameMode的BeginPlay中进行GameState的设置
    GameMode只在服务器有一份数据

    PlayerController登录服务器后
    从GameState中获取所有玩家的PlayerState
*/