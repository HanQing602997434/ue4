
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
*/