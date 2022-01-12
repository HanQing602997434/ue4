
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

        选择Select后，将会创建一个名为Blueprint的新默认类。

        这时设计师更改TotalDamage为300，将DamageTimeInSeconds更改为2秒。这就是属性现在的显示方式。

        计算值与我们的预期不符。它应该是150，但它仍然是默认值200。原因是我们只在加载过程中初始化属性
        之后才计算我们的每秒伤害值。不考虑编辑器的运行时更改。这个问题有一个简单的解决方案，因为引擎
        会在编辑器中更改目标对象时通知它。下面的代码显示了在编辑器中计算派生值所需的附加挂钩。

            void AMyActor::PostInitProperties()
            {
                Super::PostInitProperties();

                CalculateValues();
            }

            void AMyActor::CalculateValues()
            {
                DamagePerSecond = TotalDamage / DamageTimeInSeconds;
            }

            #if WITH_EDITOR
            void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent)
            {
                CalculateValues();

                Super::PostEditChangeProperty(PropertyChangeEvent);
            }
            #endif

        需要注意的是，该PostEditChangeProperty方法位于特定于Editor的#ifdef。这样一来，构建游戏只会编译
        实际需要的代码，删除任何可能不必要地增加可执行文件大小的额外代码。现在我们已经编译了该代码，该
        DamagePerSecond值与我们期望的值匹配。

    跨C++和蓝图边界调用函数
        到目前位置，我们已经展示了如何向蓝图公开属性，但在深入了解引擎之前，我们应该介绍最后一个介绍性主题。
        在创建游戏系统时，设计师需要能够调用由C++程序员创建的函数。程序员还需要能够从C++代码调用在蓝图中实
        现的函数。让我们首先让CalculateValues()函数可以从蓝图中调用。向蓝图公开函数就像公开属性一样简单。
        它只需要在函数声明之前放置一个宏！下面的代码片段显示了此操作所需的内容。
            UFUNCTION(BlueprintCallable, Category="Damage")
            void CalculateValues();
        UFUNCTION()宏把手暴露给C++函数的反射系统。该BlueprintCallable选项将其公开给蓝图虚拟机。每个蓝图
        公开的功能都需要一个与之关联的类别，以便右键单机上下文菜单正常工作。
        
        该功能可从"损坏"类别中选择。下面的蓝图代码显示了TotalDamage值的变化，随后调用了重新计算相关数据。
        这使用我们之前添加的相同函数来计算我们的依赖属性。大部分引擎通过UFUNCTION()宏暴露给蓝图，因此人们
        无需编写C++代码即可构建游戏。但是，最好的方法时使用C++构建基本游戏系统和性能关键代码，并使用蓝图自
        定义行为或从C++构建块创建复合行为。

        现在设计人员可以调用我们的C++代码，让我们探索一种更强大的方法来跨越C++/蓝图边界。这种方法允许C++
        代码调用蓝图中定义的函数。我们经常使用这种方法来通知设计师他们可以在他们认为合适的情况下响应事件。
        这通常包括产生效果或其他视觉影响，例如隐藏或取消隐藏演员。下面的代码片段显示了一个由蓝图实现的函数。
            UFUNCTION(BlueprintImplementableEvent, Category="Damage")
            void CalledFromCpp();
        该函数的调用方式与任何其他C++函数一样。在幕后，虚幻引擎会生成一个基本的C++函数实现，该实现了解如何
        调用蓝图VM。这通常称为Thunk。如果所讨论的蓝图没有为此方法提供函数体，则该函数的行为就像一个没有主体
        的C++函数；它什么都不做。如果您想提供C++默认实现，同时仍允许蓝图覆盖该方法，该怎么办？UFUNCTION()
        宏也有一个选项。下面的代码片段实现这一点所需的更改。
            UFUNCTION(BlueprintNativeEvent, Category="Damage")
            void CalledFromCpp();
        
        此版本仍会生成调用蓝图VM的thunking方法。那么如何提供默认实现呢？这些工具还会生成一个新的函数声明，
        看起来像<function name>_Implementation()。必须提供此版本的功能，否则项目将无法链接。
            void AMyActor::CalledFromCpp_Implementation()
            {
                // Do something cool here
            }
        现在，当相关蓝图未覆盖该方法时，将调用此版本的函数。请注意，在以前版本的构建工具中，_Implementation()
        声明是自动生成的。在4.8以及更高的版本中，必须将其显式添加到标题中。

    虚幻对象[UObject]
        引擎中的基本构建块称为UObject。这个类，加上UClass，提供了一些引擎最重要的服务：
            属性和方法的反射
            属性序列化
            垃圾收集
            UObject按名称查找
            属性的可配置值
            对属性和方法的网络支持
        每个派生自类UObject都有一个UClass为其创建的单例，其中包含有关类实例的所有元数据。UObject和UClss一起
        是一切的根，它的寿命期和一个游戏对象一样。考虑aUClass和a之间区别的最好方法UObject是UClass描述a的实例
        将是什么样子，哪些属性可用于序列化、网络等等。大多数游戏玩法开发不涉及直接派生自UObject，而是从AActor
        和UActorComponet派生。你不需要知道UClass或UObject工作的细节编写游戏代码，但很高兴知道这些系统的存在。

    演员[Actor]
        AActor是UObject游戏体验的一部分。Actor要么由设计师放置在关卡中，要么在运行时通过游戏系统创建。所有可以
        放入关卡的对象都从这个类扩展而来。实例包括AStaticMeshActor，ACameraActor和APointLight。由于AActor派
        生自UObject，因此它享有上一节中列出的所有标准功能。Actor可以通过游戏代码（C++或蓝图）或从内存中卸载拥有
        的关卡时通过标准垃圾收集机制显示销毁。Actor负责游戏对象的高级行为。

        Actor有一系列在其声明周期中被调用的事件。
            BeginPlay：当Actor在游戏过程中首次出现时调用。
            Tick：每帧调用一次以随着事件的推移进行工作。
            EndPlay：当对象离开游戏空间时调用。

    运行时声明周期
        Actor被加载并开始存在，最终关卡被卸载，Actor被销毁。

    UActor组件[UActorComponent]
        一个Component只能附加到一个父Component或Actor，但它可能有许多附加到自己的子Components。想象一棵组件树。
        子组件具有相对于其父组件或Actor的位置、旋转和缩放。
            RootComponent：这时AActor在Actor的组件树中拥有顶级组件的成员
            Ticking：组件作为拥有ActorTick函数的一部分进行标记。一定要Super::Tick在编写自己的Tick函数时调用。

    结构[UStruct]
        UStruct实例不会被垃圾收集。如果创建它们的动态实例，必须自己管理它们的生命周期。AUStruct应该时一个普通数据
        类型，具有UObject反射支持，可在虚幻编辑器中进行编辑、蓝图操作、序列化、网络等。

    虚幻反射系统
        UE4使用自己的反射实现，支持垃圾收集、序列化、网络复制和蓝图/C++通信等动态功能。这些功能是可选的，这意味着必
        须为您的类型添加正确的标记，否则Unreal将忽略它们并且不会为它们生成反射数据。
            UCLASS()：用于告诉Unreal为类生成反射数据，该类必须派生自UObject。
            USTRUCT()：用于告诉Unreal为结构生成反射数据。
            GENERATED_BODY()：UE4将其替换为为该类型生成的所有必要样板代码。
            UPROPERTY()：允许将UCLASS或USTRUCT的成员变量用作UPROPERTY。UPROPERTY有很多用途。它可以允许从蓝图中
                复制、序列化和访问变量。垃圾收集器也使用它们来跟踪对象UObject。
            UFUNCTION()：允许将UCLASS或USTRUCT的类方法用作UFUNCTION。UFUNCTION可以允许从蓝图中调用类方法并将其
            用作RPC等。

        UCLASS的示例声明：
            #include "MyObject.generated.h"

            UCLASS(Blueprintable)
            class UMyObject : public UObject
            {
                GENERATED_BODY()

            public:
                UMyObject();

                UPROPERTY(BlueprintReadOnly, EditAnywhere)
                float ExampleProperty;

                UFUNCTION(BlueprintCallable)
                void ExampleFunction();
            };
        包含MyObject.generated.h。UE4会生成所有的反射数据并放入这个文件中。必须将此文件作为最后一个包含在声明类型的
        头文件中。

        UCLASS，UPROPERTY和UFUNCTION标记，添加一些常见的说明符。这些允许我们指定某些行为或属性。
            Blueprintable：此类可以通过蓝图进行扩展。
            BlueprintReadOnly：该属性可以从蓝图中读取，但不能写入。
            EditAnywhere：此属性可以通过属性窗口、原型和实例进行编辑。
            Category：定义此属性出现在编辑器的详细信息视图中的哪个部分。这有助于组织目的。
            BlueprintCallable：该函数可以从蓝图中调用。

    对象/参与者迭代器
        对象迭代器是迭代特定UObject类型及其子类的所有实例非常有用的工具。
            for (TObjectInterator<UObject> It; It; ++It)
            {
                UObject* CurrentObject = *It;
                UE_LOG(LogTemp, log, TEXT("Found UObject named: %s"), *CurrentObject->GetName());
            }
        可以通过为迭代器提供更具体的类型来限制搜索范围。假设有一个名为UMyClass的类，派生自UObject。可以这样找到所有
        实例：
            for (TObjectInterator<UMyClass> It; It; ++It)
            {
                // ...
            }

        Actor迭代器和对象迭代器非常相似，但仅适用于派生自AActor的对象。
        创建Actor迭代器时，需要给它一个指向UWorld实例的指针。许多UObject类，例如APlayerController，提供了一个GetWorld
        方法。如果不确定，可以查看a上的ImplementsGetWorld方法UObject，看是否实现了GetWorld方法。
            APlayerController* MyPC = GetMyPlayerControllerFromSomewhere();
            UWorld* World = MyPC->GetWorld();

            // Like object iterators, you can provide a specific class to get only objects that are
            // or derive from that class
            for (TActorInterator<AEnemy> It(World); It; ++It)
            {
                // ...
            }
            NOTE
                由于AActor派生自UObject，因此也可以使用TObjectIterator来查找实例AActors。在PIE中要小心！

    内存管理和垃圾收集
        UOjects和垃圾收集
            UE4使用反射系统来实现垃圾回收系统。使用垃圾回收，不必手动管理删除UObject实例，只需要维护对它们的有效引用。
            类需要派生自UObject才能启用垃圾收集。
            在垃圾收集器中，有一个概念叫做根集。根集时收集器知道永远不糊ibei垃圾收集的对象列表。只要存在从根集中的对象
            到相关对象的引用路径，对象就不会被垃圾回收。如果一个对象不存在到根集这样的路径，则它被称为不可达并且将在下
            次垃圾收集器运行时被收集（删除）。引擎以一定的时间间隔运行垃圾收集器。

        Actors和垃圾收集
            除了关卡关闭期间，Actor通产不会被垃圾回收。生成后，必须手动调用Destory它们以将它们从关卡中移除而不结束关卡。
            它们将立即从游戏中删除，然后在下一个垃圾收集阶段完全删除。

        结构
            UStructs不能被垃圾收集。如果必须使用动态实例UStructs，使用智能指针。

        非UObject引用
            普通C++对象（不是派生UObject的）也可以添加对对象的引用并防止垃圾收集。对象必须从FGCObject派生并覆盖其
            AddReferencedObjects方法。

    类命名前缀
        虚幻引擎提供了在构建过程中生成代码的工具。这些工具有一些类命名期望，如果名称与期望不匹配，将触发警告或错误。
            从Actor派生的类以A为前缀，例如AContorller。
            从Object派生的类以U为前缀，例如UComponent。
            枚举以E为前缀，例如EFortificationType。
            接口类通常以I为前缀，例如IAbilitySystemInterface。
            模板类以T为前缀，例如TArray。
            派生自SWidget(Slate UI)的类以S为前缀，例如SButton。
            其他所有内容都以字母F为前缀，例如FVector。

    数值类型
        由于不同平台对于short、int和long等基本类型有不同的大小，因此UE4提供了以下类型：
            int8/uint8：8位有符号/无符号整数
            int16/uint16：16位有符号/无符号整数
            int32/uint32：32位有符号/无符号整数
            int64/uint64：64位有符号/无符号整数
        标准float(32位)和double(64位)类型也支持浮点数

    字符串
        UE4提供了几个不同的类来处理字符串
        FString是一个可变字符串，类似std::string。FString有大量的方法可以轻松处理字符串。要创建一个新的FString，
        请使用TEXT宏：
            FString MyStr = TEXT("Hello, Unreal 4!")

    文本
        FText类似与FString，但它适用于本地化文本。要创建一个新的FText，请使用NSLOCTEXT宏。此宏采用默认语言的命名
        空间、键和值：
            FText MyText = NSLOCTEXT("Game UI", "Health Warning Message", "Low Health!")
        也可以使用LOCTEXT宏，只需为每个文件定义一次命名空间。确保在文件底部取消定义它。
            #define LOCTEXT_NAMESPACE "Game UI"

            FTEXT MyText = LOCTEXT("Health Warning Message", "Low Health!")

            #undef LOCTEXT_NAMESPACE

    名称
        FName将重复出现的字符串存储为标识符，以便在比较它们时节省内存和CPU时间。FName使用映射到给定字符串的较小存储
        占用索引。

    TCHAR
        TCHAR类型用作一个独立于所使用字符集的字符存储方式。在底层，UE4字符串使用TCHAR数组以UTF-16编码存储数据。可以
        使用重载的解引用运算符访问原始数据，该运算符返回TCHAR。

        这对于某些函数是必需的，例如FString::Printf，"%s"字符串格式说明符需要TCHAR而不是FString。
            FString Str1 = TEXT("World");
            int32 Val1 = 123;
            FString Str2 = FString::Printf(TEXT("Hello, %s! You have %i points."), *Str1, Val1);
        
        该FChar类型提供了一组用于处理单个TCHAR字符的静态实用程序函数。
            TCHAR Upper('A');
            TCHAR Lower = FChar::ToLower(Upper); // 'a'
            NOTE
                该FChar类型定义为TChar<TCHAR> （在API中列出）。

    容器
        容器的主要功能是存储数据集合的类。这些类中最常见的是TArray，TMap和TSet。其中每一个都是动态大小的。

    数组
        虚幻中使用的主要容器是TArray，它的功能与std::vector非常相似，但提供了很多功能。
        TArray具有将其元素垃圾收集的额外好处。

    TMap
        TMap是键值对的集合，类似于std::map。TMap具有根据键查找、添加和删除元素的快速方法。可以使用任何类型的键，只要
        它具有GetTypeHash为它定义的函数。

    TSet
        TSet存储唯一值的集合，类似于std::set。尽管TArray它的AddUnique和Contains方法支持类似集合的行为，但TSet这些
        操作的实现速度更快，并且可以防止自动添加非唯一元素。

    容器迭代器
        使用迭代器，可以遍历容器的每个元素。
            for (auto EnemyIterator = Enemy.CreateIterator(); EnemyIterator; ++EnemyIterator)
            {

            }

    For-each循环
        每个容器类还支持"for each"样式语法来循环元素。TArray和TSet返回每个元素，而TMap返回一个键值对。

    使用自定义类型和TSet/TMap（哈希函数）
        创建自己的类并希望在a中使用它TSET，或者作为a中的键TMap，则需要提供一个散列函数。
*/