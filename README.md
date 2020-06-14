# Tafang
Change log：
  3rd version增加的内容：新增class：enemy，公有成员有draw，move函数，公有槽函数doActive。
私有成员m_maxHP,m_currentHP,m_speed,m_active,m_pos,m_sprite等，用于敌人的实现
  在mainwindow.h新增loadWave加载敌人信息，updateMap用来更新状态，增加QList m_enemyList来管理敌人信息
  新增头文件utility.h，用于储存常用的公有函数，目前有collisionWithCircle，目的是检测敌人是否进入了塔的攻击范围
  修改的内容：修改了waypoint的顺序，现在waypoint是从出口到入口而不是相反
  实现了让敌人从入口走到出口
 4th version增加的内容：新增class:bullet，用于子弹的实现，有函数draw，move，私有成员m_currentPos,m_startPos,m_targetPos等。
   在enemy类中新增了与防御塔攻击有关的函数，比如受伤时的getDamaged函数，死亡时getremoved函数
   同样，在tower类新增了攻击有关成员，比如攻击频率m_firerate，攻击目标choosEenemy，判断敌人进入攻击范围时的checkEnemyinRange（）函数
   在mainwindow部分也进行了相应的修改，来调用这些新的成员函数。
   删除的内容：删除了怪物路线以及防御塔攻击范围的绘制，使游戏界面更加美观
   修改的内容：将怪物和防御塔的图像换为PS过的图，显得更加美观。
