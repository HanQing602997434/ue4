
// UE4中的C++编程简介
/*
    虚幻C++太棒了！
        我们喜欢将Unreal C++视为"辅助C++"，因为有很多特性可以帮助每个人更轻松地使用C++

    C++和蓝图
        UE4提供了两种方法，C++和Blueprint Visual Scripting，来创建新的游戏元素。使用C++，
        程序员可以添加基本的游戏系统，然后设计师可以在这些系统上构建或使用这些系统来为关卡或
        游戏创建自定义游戏。
        在类中，我们将创建一些设计师可以设置的属性，并且我们将从这些属性中派生出新的值。使用
        我们为您提供的工具和C++宏，整个过程非常容易。

    类向导
        我们要做的第一件事是使用编辑器中的类向导生成基本的C++类，稍后将由蓝图扩展。

        一旦选择创建类，向导将生成文件并打开您的开发环境，以便您开始编辑它。这是为您生成的类
        定义。

        类向导生成您的类BeginPlay并Tick指定为覆盖。BeginPlay是一个让您知道Actor已进入游戏
        处于可玩状态的事件。这是为您的班级启动游戏逻辑的好地方。Tick每帧调用一次，自上次调用
        以来经过的时间量。您可以在那里执行任何重复逻辑。但是，如果不需要该功能，最好将其删除
        以节省少量性能。如果删除它，请确保删除构造函数中指示应该发生滴答的行。

    在编辑器中显示属性
        可以创建一些设计师可以在编辑器中设置的属性。使用说明符很容易公开给编辑器UPROPERTY。
        你所要做的就是把UPROPERTY(EditAnywhere)声明在财产上面的行。
            UPROPERTY(EditAnywhere)
            int32 TotalDamage;

        这就是您在编辑器中编辑该值所需要做的一切。还有更多方法可以控制编辑的方式和位置。这
        是通过将更多信息传递给说明UPROPERTY()符来完成的。例如，如果您希望TotalDamage属性
        出现在具有相关属性的部分中，您可以使用分类功能：
            UPROPERTY(EditAnywhere, Category="Damage")
            int32 TotalDamage;
        当用户希望编辑此属性时，它现在与您使用此类别名称标记的任何其他属性一起出现在"损坏"。
        这是将常用设置放在一起以供设计师编辑的好方法。

        现在我们将相同的属性公开给蓝图：
            UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
            int32 TotalDamage;
        有一个说明符使属性可用于在蓝图图形中读取和写入。BlueprintReadOnly如果您希望将属性
        视为const蓝图中的属性，则可以使用单独的说明符。有很多选项可用于控制属性如何向编辑器
        公开。

        让我们为示例类添加几个属性。已经有一个属性可以控制这个actor将造成的伤害总量，但让我
        们更进一步，让伤害随着事件的推移而发生。下面的代码添加了一个设计器可设置属性和一个对
        设计器可见但不能由他们更改的属性。
            UCLASS()
            class AMyActor : public AActor
            {
                GENERATED_BODY()
            public:

                UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
                int32 TotalDamage;

                UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
                float DamageTimeInSeconds;

                UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category="Damage")
                float DamagePerSecond;

                ...
            }
        DamageTimeInSeconds是设计者可以修改的属性。该DamagePerSecond属性是使用设计器的设置
        计算得出的值。说明符VisibleAnywhere将该属性标记为可查看但不可编辑。说明符Transient
        意味着它不会被保存或从磁盘加载；它是派生的、非持久的值，因此不需要存储它。

    在构造函数中设置默认值
        在构造函数中为属性设置默认值的工作方式与典型的C++类相同。下面是在构造函数中设置默认值
        的两个示例。并且在功能上是等效的：
            AMyActor::AMyActor()
            {
                TotalDamage = 200;
                DamageTimeInSeconds = 1.0f;
            }

            AMyActor::AMyActor() :
                TotalDamage(200),
                DamageTimeInSeconds(1.0f)
            { 
            }

        为了支持每个实例设计器设置的属性，还从给定对象的实例数据中加载值。此数据在构造函数之后应
        用。可以通过连接到PostInitProperties()调用链来根据设计者设置的值创建默认值。这是该过程
        的示例，其中TotalDamage和DamageTimeInSeconds是设计者指定的值。即使这些是设计者指定的，
        仍然可以为他们提供合理的默认值：
            NOTE
                如果没有为属性提供默认值，引擎将自动将该属性设置为零，或者在指针类型的情况下为null。
            void AMyActor::PostInitProperties()
            {
                Super::PostInitProperties();
                DamagePerSecond = TotalDamage / DamageTimeInSeconds;
            }

    热重载
        这是Unreal的一个很酷的功能，如果您习惯在其他项目中使用C++编程，在不关闭编辑器的情况下编
        译C++更改！有两种办法可以做到这一点：
            1.在编辑器仍在运行的情况下，继续像往常一样从Visual Studio构建。编辑器将检测新编译
            的DLL并立即重新加载更改！

            2.或者，只需单机编辑器主工具栏上的编译按钮。
        
    通过蓝图扩展C++类
        到目前位置，我们已经使用C++类向导创建了一个简单的游戏类，并添加了一些属性供设计师设置。
        现在，让我们看看设计师如何从我们卑微的七点开始创建独特的类。

        我们要做的第一件事是从我们的AMyActor类中创建一个新的蓝图类。
*/