
// 蓝图
/*
    AIController
        ai控制器

    Behavior Tree
        行为树

    Blackbord
        黑板

    Decorator
        装饰

    Service
        服务

    AI流程
        创建AI -》 创建AIController并设置为AI的AI Controller Class -》 RunBehaviorTree -》 设置行为树 -》 执行各种行为 -》 Sequence序列 -》 Selector选择器

    ApplyDamage
        造成伤害函数

    Event AnyDamage
        受到伤害事件

    GetPlayerPawn
        返回指定玩家索引处的玩家Pawn

    RInterpTo
        让物品始终朝向摄像机，让物体调整角度的效果更有动感，Current和Target分别表示当前角度和目的角度，
        DeltaTime为间隔时间，一般设置为我们计算机计算每帧的时间，Interp speed为调整的速度，越小速度越
        慢，一般调整为5左右效果比较好

    GetWorldDeltaSeconds
        获取电脑性能1帧运行多少秒

    GetActorRotation
        获取玩家的旋转
    
    BreakRotator
        拆分玩家的Rotator。Roll，绕着x轴旋转的角度；Pitch，绕着y轴旋转的角度；Yaw，绕着z轴旋转的角度

    MakeRotator
        合成玩家的Rotator。

    MultiSphereTraceForObjects
        球形范围检测，获取目标

    动画蓝图
        所有动画中的通知可以在动画蓝图中获取事件

    事件
        事件是从游戏代码调用以开始执行EventGraph中的单个网络的节点。它们使蓝图能够执行一系列动作以响应
        游戏中发生的某些事件，例如游戏开始时、关卡重置时或玩家受到伤害时。
        可以从蓝图中访问事件以实现新功能或覆盖或增强默认功能。可以在单个EventGraph中使用任意数量的事件；
        尽管每种类型只能使用一种。
        一个事件只能执行一个对象。如果你想从一个事件中触发多个动作，你需要将它们线性地串在一起。

        EventLevelReset
            当关卡重新启动时，Level Reset事件会发生一个执行信号。当您需要在关卡重新加载后触发某些内容
            时，这很有用，例如在玩家死亡但关卡不需要重新加载的游戏情况下。

        EventActorBeginOverlap
            当同时满足多个条件时，将执行此事件：
                参与者之间的碰撞响应必须允许重叠。
                执行事件的两个Actor都将Generate Overlap Events设置为true。
                最后，两个Actor的碰撞开始重叠；一起移动或创建一个重叠另一个。

        EventActorEndOverlap
            当同时满足多个条件时，将执行此事件：
                参与者之间的碰撞响应必须允许重叠。
                执行事件的两个Actor都将Generate Overlap Events设置为true。
                最后，两个Actor的碰撞停止重叠；分开或如果一个被摧毁。    
*/