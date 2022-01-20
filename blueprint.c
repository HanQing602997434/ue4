
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

    RInterp To
        让物品始终朝向摄像机，让物体调整角度的效果更有动感，Current和Target分别表示当前角度和目的角度，
        DeltaTime为间隔时间，一般设置为我们计算机计算每帧的时间，Interp speed为调整的速度，越小速度越
        慢，一般调整为5左右效果比较好

    Get World Delta Seconds
        获取电脑性能1帧运行多少秒

    GetActorRotation
        获取玩家的旋转
    
    Break Rotator
        拆分玩家的Rotator。Roll，绕着x轴旋转的角度；Pitch，绕着y轴旋转的角度；Yaw，绕着z轴旋转的角度

    Make Rotator
        合成玩家的Rotator。

    MultiSphereTraceForObjects
        球形范围检测，获取目标
*/