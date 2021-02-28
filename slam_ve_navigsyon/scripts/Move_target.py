#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rospy
import actionlib
#Bu satır, gezinme yığınına yüksek seviyeli bir arayüz sunan bir ROS eylemi olan move_base
#için eylem özelliğini içerir. Esasen, move_base eylemi istemcilerden gelen hedefleri kabul eder 
#ve robotu dünyada belirtilen konuma / yöne hareket ettirmeye çalışır.
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal

def movebase_client():

    # Bu satır, MoveBaseAction arayüzüne bağlı olan "move_base" adlı eylemle iletişim kurmak
    # için kullanacağımız bir eylem istemcisi oluşturur.
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)

    # Hedef nokta gelene kadar servis bekleniyor.
    client.wait_for_server()

    # Hedef noktası belirlemek için MoveBaseGoal mesajı kullanılıyor.
    target = MoveBaseGoal()
    target.target_pose.header.frame_id = "map"

    #map üstündeki x ye kordinayları tanımlanır.
    target.target_pose.pose.position.x = -2
    target.target_pose.pose.position.y = -4

    # robotun duracagı noktada acısını ayarlama
    target.target_pose.pose.orientation.w = 1.0

    #hedef aksiyon servirina gönderilir.
    client.send_goal(target)

    #aksiyonun bitmesini bekler 
    wait = client.wait_for_result()

    if not wait:
        rospy.signal_shutdown("Action Servisi yok!")
    else:
        return client.get_result()

#Main için gerekli yapılandırma yapılır.
if __name__ == '__main__':
    try:
        rospy.init_node('Move_Target')
        result = movebase_client()
        if result:
            rospy.loginfo("Hedef noktaya varıldı!")
        else:
            rospy.loginfo("Hedefe gidiliyor...")
    except rospy.ROSInterruptException:
        pass
