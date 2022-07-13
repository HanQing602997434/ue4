
// UE4服务器架构
/*
    如何搭建UE4服务器框架
        思路：
            玩家通过socket连接到数据服务器，通过数据服务器来管理专用服务器

        问题：
            如何创建专用服务器并返回数据给数据服务器？
            重写HorusServer。
            深入理解Advance Session
	    专用服务器启动不一样的地图
	    开始的服务器的session是什么
	    Advance Session版本问题
*/
