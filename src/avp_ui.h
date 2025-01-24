#ifndef AVP_UI_H
#define AVP_UI_H

#include <QWidget>
#include <ros/ros.h>
// #include <cv_bridge/cv_bridge.h>
// #include <sensor_msgs/Image.h>
// #include <sensor_msgs/CompressedImage.h>
#include <std_msgs/Int16.h>
// #include <sensor_msgs/image_encodings.h>
#include "localization_msgs/localization.h"
#include "planning_msgs/TrajectoryStamped.h"
#include "planning_msgs/TrajectoryPoint.h"

#include "perception_msgs/ParkingSlot.h"
#include "perception_msgs/ParkingSlots.h"

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
// #include <message_filters/sync_policies/exact_time.h>

#include <unistd.h>

namespace Ui {
class avp_ui;
}

// typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::CompressedImage, localization_msgs::localization> MySyncPolicy;


class avp_ui: public QWidget
{
    Q_OBJECT

public:
    explicit avp_ui(QWidget *parent = 0);
    ~avp_ui();

    // void img_callback(const sensor_msgs::CompressedImageConstPtr& msg);
    void planning_state_callback(const std_msgs::Int16::ConstPtr& msg);
    // void locked_carport_callback(const std_msgs::Int16::ConstPtr& msg);
    void localization_callback(const localization_msgs::localization::ConstPtr& msg);
    void trajectory_callback(const planning_msgs::TrajectoryStamped::ConstPtr& msg); 
    // void img_location_callback(const sensor_msgs::CompressedImageConstPtr& msg1, const localization_msgs::localization::ConstPtr& msg2);
    // void parkingslot_callback(const perception_msgs::ParkingSlots::ConstPtr& msg);
    // void draw_traj_points();

    bool m_isPaused = false;
    bool m_isTerminated = false;



signals:
    // void imageSignal(cv::Mat);
    // void planningStateSignal(Int16 value);
    // void lockedCarportSignal(Int16 value);
public slots:
// private slots:
    // void on_slider_value_change(int value);
    // void on_btnStart_clicked();
    // void on_btnSelectCarport_clicked();
    // void displayMat(cv::Mat image);
    void on_btnStart_toggled();
    void on_btnPause_toggled();
    void timerSlot();

private:
    Ui::avp_ui *ui;

    // ros::NodeHandle n;
  
    // ros::Publisher select_carport_publisher;
    ros::Publisher button_start_publisher;

    ros::Publisher sync_publisher;
    ros::Publisher termination_publisher;
    ros::Publisher pause_publisher;



    // ros::Subscriber image_sub;
    ros::Subscriber planning_state_sub;
    // ros::Subscriber locked_carport_sub;
    // ros::Subscriber subscription_parking_slots;

    ros::Subscriber localization_sub;
    ros::Subscriber traj_sub;

    // message_filters::Subscriber<sensor_msgs::CompressedImage>* img_sub;             // topic1 输入
    // message_filters::Subscriber<localization_msgs::localization>* location_sub;   // topic2 输入
    // message_filters::Synchronizer<MySyncPolicy>* sync;   


    // cv::Mat image;
    int planning_state = 0;
    int locked_id = -1;

    localization_msgs::localization realtime_car_location;
    std::vector<planning_msgs::TrajectoryPoint> traj_points;
    planning_msgs::TrajectoryPoint target_point;
    perception_msgs::ParkingSlot target_carport;
    // std::vector<perception_msgs::ParkingSlot> record_parkingslot; // record parking slot


    double h_size = 29.95;
    double w_size = 29.9375;

    int width = 479;
    int height = 599;

    double car_length = 3.495;
    double car_back_susp = 0.481;
    // double car_back_susp = 0.535;

    double W_limit = 16;
    double H_limit = 20;

    bool pause_signal = false; //true为处于暂停状态 false为继续运行状态

    ros::Time current_localization_timestamp = ros::Time(0.0);
    // ros::Time current_img_timestamp = ros::Time(0.0);
    // ros::Time current_slot_timestamp = ros::Time(0.0);







};

#endif 
