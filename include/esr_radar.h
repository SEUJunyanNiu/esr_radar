#ifndef ESR_RADAR_H_
#define ESR_RADAR_H_
#include <ros/ros.h>
#include <string>

#include <esr_radar/Object.h>
#include <esr_radar/Objects.h>
#include <can_msgs/FrameArray.h>
#include<jsk_recognition_msgs/BoundingBox.h>
#include<jsk_recognition_msgs/BoundingBoxArray.h>
#include<cmath>
 

class EsrRadar 
{
public:
	 EsrRadar();
	~EsrRadar(){};
	
	bool init();
	void run();
private:
	void sendMsgToEsr(const ros::TimerEvent&);
	void canMsg_callback(const can_msgs::FrameArray::ConstPtr& msg);
	void parse_msg(const can_msgs::Frame &frame);
	void pubBoundingBoxArray();
	
	enum MeasurementStatus
	{
		NoTarget           = 0,
		NewTarget          = 1, //新目标  ，新检测到的目标
		UpdateTarget       = 3, //更新目标，由检测和状态估计得到的目标
		CoastedTarget      = 4, //滑行目标，当前时刻未检测到，根据上一时刻状态推测当前状态
		InvalidCoastTarget = 6,
	};
	
private:
	ros::Subscriber sub_can_;
	ros::Publisher  pub_bbox_;
	ros::Publisher  pub_objects_;
	
	std::string from_can_topic_;
	std::string to_can_topic_;
	
	jsk_recognition_msgs::BoundingBoxArray bbox_array_;
	jsk_recognition_msgs::BoundingBox      bbox_;

	esr_radar::Objects esr_objects_;
	esr_radar::Object  esr_object_;
	
	bool is_sendMsgToEsr_;
	
	ros::Timer timer_;
	
};

#endif
