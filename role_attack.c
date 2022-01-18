
// 如果做出角色攻击
/*
    概念
        RootMotion
            位移动画，攻击可以移动

        InPlace
            原地动画，攻击不移动

    流程
        1.从Animations动画中的RootMotion挑出一个攻击动画

        2.右键创建动画蒙太奇

        3.在PlayerChar创建事件DoAttack

        4.选择对应的蒙太奇动画

        5.在PlayerController中获取Input中的Attack事件

        6.需要将动画中的RootMotion下的EnableRootMotion勾上
*/