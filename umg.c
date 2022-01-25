
// UMG
/*
    CreateUIWidget
        创建UI，class指定要创建的UI

    AddtoViewport
        添加到玩家屏幕

    RemovefromParent
        从父类移除UI

    FlipFlop
        触发器，检测同一按键的多次输入，第一次按键为A，第二次按键为B

    Canvas Panel Designer面板
        Tool Tip Text
            当用户用鼠标悬停在控件上时显示的工具提示文本

        is Enabled
            是否启用

        Visibility
            可视化

        Render Opacity
            渲染不透明度

        Tool Tip Widget
            当用户用鼠标悬停在控件上时显示UI

    Text Block
        Slot
            控件属于那个画布的插槽

            Anchors
                锚点，控件显示的位置

            Alignment
                控制对齐

            Size to Content
                自适应大小

        Content
            内容

        Appearance
            外观

            Color and Opacity
                颜色和不透明度

        Font
            字体

            Font Family
                字体系统

            Typeface
                二级字体

            Size
                字体大小

            Font Material
                字体材质

            Outline Settings
                边框设置

                Outline Size
                    边框大小

                Separate Fill Alpha
                    边框分离

                Apply Outline to Drop
                    边框阴影

                Outline Material
                    边框材质

                Outline Color
                    边框颜色

        Strike Brush
            下划线

        Shadow Offset
            阴影偏移，阴影投射的角度

        Shadow Color
            阴影颜色

            Min Desired Width
                最小期望宽度
            
            Justification
                自适应对齐

        Wrapping
            包装
        
            Auto Wrap Text
                文本自动换行

            Wrap Text At
                文本换行的阈值

        Pivot
            旋转支点

        Clipping
            剪切，屏幕之外进行剪切

    UI响应玩家输入
        1.在UI的Graph的function中重载OnKeyDown
        2.在事件Event Construct中设置焦点SetKeyboardFocus
        3.在Designer界面选择最上层的UI，在Details面板设置Is Focusable为真

        Return Node节点的Return Value
            如果连 接的是Handled表示输入已处理完，不再向下执行输入逻辑
            如果连接的是Unhandled表示输入未处理完，继续向下执行输入逻辑
*/