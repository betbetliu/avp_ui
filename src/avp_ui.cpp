#include "avp_ui.h"
#include "avp_ui/ui_avp_ui.h"

#include <QString>
#include <std_msgs/String.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
// #include <QMetaType> 
#include <QImage>
#include <QTimer>

#include <cmath>



void avp_ui::timerSlot()
{
    ros::spinOnce();
}


void avp_ui::on_btnStart_toggled()
{   
    // if (checked)
    if (ui->btnStart->isChecked())
    {
        std_msgs::Int16 msg;
        msg.data = 1;
        // usleep(10000);
        button_start_publisher.publish(msg);
        ROS_INFO("publish the start signal!");
        ui->btnStart->setText("终止泊车");
        // ui->btnStart->setChecked(false);
        // ui->btnSelectCarport->setEnabled(true);

        
    }
    else
    {
        std_msgs::Int16 msg;
        msg.data = 1;
        // usleep(10000);
        termination_publisher.publish(msg);
        // ROS_INFO("close");
        ROS_INFO("terminate the parking process!");
        // ui->btnStart->setText("即将关闭");
        // ui->btnStart->setChecked(true);
        sleep(1);
        // exit(0);
        this->close();
        qApp->quit();

    }
}


// void avp_ui::on_btnStart_clicked()
// {
//   std_msgs::Int16 msg;
//   msg.data = 1;
//   button_start_publisher.publish(msg);
//   ROS_INFO("publish the start signal!");

//   ui->btnStart->setEnabled(false);
//   // ui->lineEdit1->setEnabled(true);
//   ui->btnSelectCarport->setEnabled(true);
// }

  void avp_ui::on_btnPause_toggled()
  {
    if (ui->btnPause->isChecked())
    {
        std_msgs::Int16 msg;
        msg.data = 1;
        // usleep(10000);
        pause_publisher.publish(msg);
        ROS_INFO("publish the pause signal!");
        ui->btnPause->setText("继续");
        // ui->btnStart->setChecked(false);
        pause_signal = true;
        // ui->lineEdit2->clear();
        // ui->lineEdit1->clear();
        ui->lineEdit3->setText("暂停泊车");
        // ui->btnSelectCarport->setEnabled(true);

        
    }
    else
    {
        std_msgs::Int16 msg;
        msg.data = 0;
        // usleep(10000);
        pause_publisher.publish(msg);
        ROS_INFO("publish the resume signal!");
        ui->btnPause->setText("暂停");
        // ui->btnStart->setChecked(true);
        pause_signal = false;
        // ui->btnSelectCarport->setEnabled(true);


    }
}




// void avp_ui::on_btnSelectCarport_clicked()
// {
//     // ui->lineEdit->setText(QString::number(value));
//     QString str = ui->lineEdit1->text();
//     int carport_id = str.toInt();

//     if (carport_id > 0)
//     {
//         std_msgs::Int16 msg;
//         msg.data = carport_id;
//         select_carport_publisher.publish(msg);
//         ROS_INFO("publish the selected carport id: %d", carport_id);

//         ui->btnPause->setEnabled(true);

//     }

// }


// void avp_ui::draw_traj_points()
// {
//     auto loc_time = current_localization_timestamp.toSec();
//     auto img_time = current_img_timestamp.toSec();
//     auto slot_time = current_slot_timestamp.toSec();

//     ROS_INFO("in draw current_localization_timestamp: %f", current_localization_timestamp.toSec());
//     int point_radius = 0.5;

//     double x_realtime = realtime_car_location.x;
//     double y_realtime = realtime_car_location.y;
//     double yaw_realtime = realtime_car_location.yaw_angle;

//     //画车位


//     if (target_carport.id > 0)
//     {
//         cv::Scalar color_carport = cv::Scalar(0,0,0);
//         double car_port_line_width = 1.0;
//         std::vector<cv::Point> cv_points;
//         for(int j= 0; j<4; j++)
//         {

//             double yaw = yaw_realtime / 180 * M_PI;

//             double x_ow = target_carport.parking_slot_point[2*j]- x_realtime;
//             double y_ow = target_carport.parking_slot_point[2*j+1] - y_realtime;

//             double x_car = x_ow * cos(yaw) + y_ow * sin(yaw);
//             double y_car = -x_ow * sin(yaw) + y_ow * cos(yaw);

//             // int x = int(width / 2 - y_car * w_size);
//             // int y = int(height / 2 + (car_length / 2 - car_back_susp - x_car) * h_size);

//             int x_carport = round(width / 2 - y_car * w_size);
//             int y_carport = round(height / 2 + (car_length / 2 - car_back_susp - x_car) * h_size);
//             cv::Point cv_point = cv::Point(x_carport, y_carport);
//             cv_points.emplace_back(cv_point);
//         }
    
//         cv::line(image, cv_points[0], cv_points[1], color_carport, car_port_line_width, cv::LINE_AA);  
//         cv::line(image, cv_points[1], cv_points[2], color_carport, car_port_line_width, cv::LINE_AA);  
//         cv::line(image, cv_points[2], cv_points[3], color_carport, car_port_line_width, cv::LINE_AA);  
//         cv::line(image, cv_points[3], cv_points[0], color_carport, car_port_line_width, cv::LINE_AA);  
//     }
//     //画车位

//     // // debug画图
//     // int plot_x_Str = int(width/2);
//     // int plot_y_Str_1 = 20;
//     // int plot_y_Str_2 = 40;
//     // int plot_y_Str_3 = 60;
//     // int plot_y_Str_4 = 80;
//     // int plot_y_Str_5 = 100;
//     // int plot_y_Str_6 = 120;

//     // cv::Scalar color = cv::Scalar(255,255,255);

//     // cv::putText(image, "x: " + std::to_string(x_realtime),cv::Point(plot_x_Str, plot_y_Str_1),
//     //                         cv::FONT_HERSHEY_SIMPLEX,0.5,color,1,1);
//     // cv::putText(image, "y: " + std::to_string(y_realtime),cv::Point(plot_x_Str, plot_y_Str_2),
//     //                         cv::FONT_HERSHEY_SIMPLEX,0.5,color,1,1);
//     // cv::putText(image, "yaw: " + std::to_string(yaw_realtime),cv::Point(plot_x_Str, plot_y_Str_3),
//     //                         cv::FONT_HERSHEY_SIMPLEX,0.5,color,1,1);
//     // cv::putText(image, "img: " + std::to_string(img_time),cv::Point(plot_x_Str, plot_y_Str_4),
//     //                         cv::FONT_HERSHEY_SIMPLEX,0.5,color,1,1);
//     // cv::putText(image, "loc: " + std::to_string(loc_time),cv::Point(plot_x_Str, plot_y_Str_5),
//     //                         cv::FONT_HERSHEY_SIMPLEX,0.5,color,1,1);
//     // cv::putText(image, "slot: " + std::to_string(slot_time),cv::Point(plot_x_Str, plot_y_Str_6),
//     //                         cv::FONT_HERSHEY_SIMPLEX,0.5,color,1,1);
//     // // debug画图

//     for(int i= 0;i<traj_points.size();i++)
//     {

//         double yaw = yaw_realtime / 180 * M_PI;

//         double x_ow = traj_points[i].x - x_realtime;
//         double y_ow = traj_points[i].y - y_realtime;

//         double x_car = x_ow * cos(yaw) + y_ow * sin(yaw);
//         double y_car = -x_ow * sin(yaw) + y_ow * cos(yaw);

//         // int x = int(width / 2 - y_car * w_size);
//         // int y = int(height / 2 + (car_length / 2 - car_back_susp - x_car) * h_size);

//         int x = round(width / 2 - y_car * w_size);
//         int y = round(height / 2 + (car_length / 2 - car_back_susp - x_car) * h_size);


//         // double x = int(width / 2 );
//         // // double y = int(height / 2 + (car_length / 2 - car_back_susp) * h_size);
//         // double y = int(height / 2);


//         if (traj_points[i].expected_speed > 0)
//         {
//             cv::circle(image, cv::Point(x, y), point_radius, cv::Scalar(255,215,10), 4);    //蓝色     
//         }
//         else if (i == 0)
//         {
//             cv::circle(image, cv::Point(x, y), point_radius, cv::Scalar(255,215,10), 4); //蓝色
//         }
//         else
//         {
//             cv::circle(image, cv::Point(x, y), point_radius, cv::Scalar(0,0,255), 4);    //红色     
//         }
//     }


// }


// void avp_ui::img_location_callback(const sensor_msgs::CompressedImageConstPtr& msg1, const localization_msgs::localization::ConstPtr& msg2)
// {
//     auto head = msg2->header;
//     // if(head.frame_id == "ow")
//     // { 
        
//     realtime_car_location.x = msg2->x;
//     realtime_car_location.y = msg2->y;
//     realtime_car_location.yaw_angle = msg2->yaw_angle;
//     ROS_INFO("recieved localization and assign realtime_car_location! ");

//     // }
//     current_localization_timestamp = head.stamp;
//     ROS_INFO("location timestamp: %f", head.stamp.toSec());

//     cv_bridge::CvImagePtr cv_ptr;
//     try
//     {   /*change to CVImage*/
//         cv_ptr = cv_bridge::toCvCopy(msg1, sensor_msgs::image_encodings::BGR8);
//         // cv_ptr = cv_bridge::toCvCopy(msg, cv_bridge::enc::BGR8);
//         ROS_INFO("recieved detection image!");
//         current_img_timestamp = msg1->header.stamp;
//         ROS_INFO("image timestamp: %f", msg1->header.stamp.toSec());

//         cv::Mat ori_image = cv_ptr->image;

//         // 获取图像的原始宽度和高度
//         int ori_width = ori_image.cols;
//         int ori_height = ori_image.rows;

//         std::cout<<"ori_width: "<< ori_width << " ori_height: "<< ori_height <<std::endl; 

//         // 计算缩放后的宽度和高度，为原来的一半
//         width = int(ori_width / 2);
//         height = int(ori_height / 2);

//         // 严重低级错误，搞混ori_width  ori_height 
//         // h_size = ori_width / ( 2 * H_limit);
//         // w_size = ori_height / ( 2 * W_limit);

//         h_size = ori_height / ( 2 * H_limit);
//         w_size = ori_width / ( 2 * W_limit);


//         // 调用resize函数，将原始图像缩放到新的尺寸，并存储到新的图像对象中
//         // 第一个参数是原始图像，第二个参数是新的图像，第三个参数是新的尺寸，第四个参数是插值方法
//         cv::resize(ori_image, image, cv::Size(width, height), cv::INTER_LINEAR);

//         // 在缩放的图上绘制轨迹点
//         if (((head.frame_id == "ow") && (pause_signal == false) && (!traj_points.empty()) &&
//              (planning_state > 0))) 
//         {
//           draw_traj_points();
//         }
//         // 在缩放的图上绘制轨迹点

//         Q_EMIT imageSignal(image);
        
//         std_msgs::Int16 msg;
//         msg.data = 1;
//         sync_publisher.publish(msg);
//         ROS_INFO("publish the sync flag: %d", msg.data);
        

//     }
//     catch (cv_bridge::Exception& e)
//     {
//         ROS_ERROR("cv_bridge exception is %s", e.what());
//         return;
//     }
// }

void avp_ui::localization_callback(const localization_msgs::localization::ConstPtr& msg)
{
    auto head = msg->header;
    ROS_INFO("localization timestamp: %f", head.stamp.toSec());

    if(head.frame_id == "ow")
    { 
        realtime_car_location.x = msg->x;
        realtime_car_location.y = msg->y;
        realtime_car_location.yaw_angle = msg->yaw_angle;
        current_localization_timestamp = msg->header.stamp;
        ROS_INFO("recieved localization and assign realtime_car_location! ");
    }
}


void avp_ui::trajectory_callback(const planning_msgs::TrajectoryStamped::ConstPtr& msg) 
{

    traj_points.clear();

    for (const auto& point : msg->traj_points) 
    {
        traj_points.push_back(point);
    }

    ROS_INFO("recieved traj points and assign traj_points! ");
}


void avp_ui::planning_state_callback(const std_msgs::Int16::ConstPtr &msg)
{
    planning_state = msg->data; 
    QString str ;

    if (pause_signal == true)
    {
        ui->lineEdit3->setText("暂停泊车");
    }
    else 
    {
        if (planning_state == 4)
        {
            str = "开始泊车";
            ui->lineEdit3->setText(str);
            ROS_INFO(" UI shows current planning state: %d", planning_state);
            // ui->btnSelectCarport->setEnabled(false);
        }
        else if (planning_state == 1)
        {
            str = "正在泊车";
            ui->lineEdit3->setText(str);
            ROS_INFO(" UI shows current planning state: %d", planning_state);
            // ui->btnSelectCarport->setEnabled(false);

        }
        else if (planning_state == 2)
        {
            str = "泊车完成";
            ui->lineEdit3->setText(str);
            ROS_INFO(" UI shows current planning state: %d", planning_state);

            // ui->btnStart->setEnabled(true); 
            // ui->btnSelectCarport->setEnabled(true);

            // ui->lineEdit1->setEnabled(false);
            // ui->btnSelectCarport->setEnabled(false);
            // ui->lineEdit2->clear();
            // ui->lineEdit1->clear();

            // sleep(5);
            // this->close();
            // qApp->quit();

            //泊车完成, 显示后关闭所有进程
            std_msgs::Int16 msg;
            msg.data = 1;
            termination_publisher.publish(msg);
            ROS_INFO("terminate the parking process!");
            // ui->btnStart->setEnabled(false);
            ui->btnStart->setText("行车完成");
            ui->lineEdit3->setText("行车完成");

            // sleep(20);
            // this->close();
            // qApp->quit();


        }
        else if (planning_state ==3)
        {
            str = "泊车失败";
            ui->lineEdit3->setText(str);
            ROS_INFO(" UI shows current planning state: %d", planning_state);

            // ui->btnStart->setEnabled(true); 
            // ui->btnSelectCarport->setEnabled(true);

            // ui->lineEdit1->setEnabled(false);
            // ui->btnSelectCarport->setEnabled(false);
            // ui->lineEdit2->clear();
            // ui->lineEdit1->clear();

            // sleep(5);
            // this->close();
            // qApp->quit();

            //当决策规划发来泊车失败，意味着AEB启动
            std_msgs::Int16 msg;
            msg.data = 1;

            termination_publisher.publish(msg);

            ROS_INFO("terminate the parking process!");

            // ui->btnStart->setEnabled(false);
            ui->btnStart->setText("行车失败");
            ui->lineEdit3->setText("行车失败");

            // sleep(20);
            // this->close();
            // qApp->quit();


        }
        else if (planning_state == 0)
        {
            str = "未开始";
            ui->lineEdit3->setText(str);
            ROS_INFO(" UI shows current planning state: %d", planning_state);
            // ui->btnSelectCarport->setEnabled(false);
        }
    }





}


// void avp_ui::locked_carport_callback(const std_msgs::Int16::ConstPtr &msg)
// {   

//     locked_id = msg->data; 
//     QString str ;
//     str = QString::number(locked_id);
//     ui->lineEdit2->setText(str);
//     ROS_INFO(" UI shows locked carport id: %d", locked_id);
// }

// void avp_ui::parkingslot_callback(const perception_msgs::ParkingSlots::ConstPtr& msg)
// {  
    

//     record_parkingslot = msg->parking_slots;
//     current_slot_timestamp = msg->header.stamp;

//     // 从 cm 化为 m
//     for(int j = 0; j < int(record_parkingslot.size()); j++)
//     {
//         for(int i = 0; i < 8; i++)
//         {
//             record_parkingslot[j].parking_slot_point[i] =  record_parkingslot[j].parking_slot_point[i] / 100;
//         }

//         if (record_parkingslot[j].id == locked_id)
//         {
//             target_carport = record_parkingslot[j];
//         }
//     } 
    
// }



// void avp_ui::img_callback(const sensor_msgs::CompressedImageConstPtr& msg)
// {
//   cv_bridge::CvImagePtr cv_ptr;
//   ROS_INFO("img timestamp: %f", msg->header.stamp.toSec());
//   current_img_timestamp = msg->header.stamp;
//   try
//   {   /*change to CVImage*/
//     cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
//     // cv_ptr = cv_bridge::toCvCopy(msg, cv_bridge::enc::BGR8);
//     ROS_INFO("recieved detection image!");
//     cv::Mat ori_image = cv_ptr->image;

//     // 获取图像的原始宽度和高度
//     int ori_width = ori_image.cols;
//     int ori_height = ori_image.rows;

//     std::cout<<"ori_width: "<< ori_width << " ori_height: "<< ori_height <<std::endl; 

//     // 计算缩放后的宽度和高度，为原来的一半
//     width = int(ori_width / 2);
//     height = int(ori_height / 2);

//     h_size = height / H_limit;
//     w_size = width / W_limit;


//     // 调用resize函数，将原始图像缩放到新的尺寸，并存储到新的图像对象中
//     // 第一个参数是原始图像，第二个参数是新的图像，第三个参数是新的尺寸，第四个参数是插值方法
//     cv::resize(ori_image, image, cv::Size(width, height), cv::INTER_LINEAR);


//     // 在缩放的图上绘制轨迹点 todo
//     if (((pause_signal == false) && (!traj_points.empty()) &&
//         (planning_state > 0))) 
//     {   
//         // // for(int i= 0;i<traj_points.size();i++)
//         // int i = 0;
//         // while(i<traj_points.size())
//         // {

//         //     double yaw = realtime_car_location.yaw_angle / 180 * M_PI;

//         //     double x_ow = traj_points[i].x - realtime_car_location.x;
//         //     double y_ow = traj_points[i].y - realtime_car_location.y;
            
//         //     std::cout<<"-----------------------" <<std::endl;
//         //     std::cout<<"car_x_ow: "<<realtime_car_location.x<<" car_y_ow: "<<realtime_car_location.y<<std::endl;
//         //     std::cout<<"x_ow: "<< traj_points[i].x <<" y_ow: "<< traj_points[i].y <<" yaw: "<< yaw <<std::endl;

//         //     std::cout<<"x-loc: "<< x_ow <<" y-loc: "<< y_ow <<" yaw: "<< yaw <<std::endl;

//         //     std::cout<<"cos(yaw): "<< cos(yaw) <<" sin(yaw): "<< sin(yaw) <<" yaw: "<< yaw <<std::endl;

//         //     double x_car = x_ow * cos(yaw) + y_ow * sin(yaw);
//         //     double y_car = -x_ow * sin(yaw) + y_ow * cos(yaw);

//         //     std::cout<<"x_car: "<< x_car <<" y_car: "<< y_car <<std::endl;


//         //     double x = int(width / 2 - y_car * w_size);
//         //     double y = int(height / 2 + (car_length / 2 - car_back_susp - x_car) * h_size);
//         //     std::cout<<"x: "<< x <<" y: "<< y <<std::endl;
//         //     std::cout<<"------------------------" <<std::endl;
            
//         //     i=i+10;

//         // }
//         // std::cout<<"traj size: "<<traj_points.size()<<std::endl;

//         draw_traj_points();
//     }
//     // 在缩放的图上绘制轨迹点

//     Q_EMIT imageSignal(image);
    
//   }
//   catch (cv_bridge::Exception& e)
//   {
//     ROS_ERROR("cv_bridge exception is %s", e.what());
//     return;
//   }

// }

// void avp_ui::displayMat(cv::Mat image)
// {
//     cv::Mat rgb;
//     QImage img;
//       if(image.channels()==3)
//       {
//           //cvt Mat BGR 2 QImage RGB
//           cv::cvtColor(image,rgb,CV_BGR2RGB);
//           img = QImage((const unsigned char*)(rgb.data),
//                       rgb.cols,rgb.rows,
//                       rgb.cols*rgb.channels(),
//                       QImage::Format_RGB888);
//       }
//       else
//       {
//           img = QImage((const unsigned char*)(image.data),
//                       image.cols,image.rows,
//                       image.cols*image.channels(),
//                       QImage::Format_RGB888);
//       }
//       ui->label_pic->setPixmap(QPixmap::fromImage(img));
//       ui->label_pic->resize(ui->label_pic->pixmap()->size());
// }


avp_ui::avp_ui(QWidget *parent):
    QWidget(parent),
    ui(new Ui::avp_ui)
{
    std::cout<<"1-1"<<std::endl;
    ui->setupUi(this);
    std::cout<<"1-2"<<std::endl;

    qRegisterMetaType<cv::Mat>("cv::Mat");
    std::cout<<"1-3"<<std::endl;

    ui->lineEdit3->setText(QString("未开始"));
    std::cout<<"1-4"<<std::endl;

    // ui->lineEdit1->setEnabled(false);
    // ui->btnSelectCarport->setEnabled(false);



    // ui->lineEdit->setText(QString::number(ui->verticalSlider->value()));
    // QObject::connect(ui->verticalSlider, SIGNAL(valueChanged(int)),
    //                  this, SLOT(on_slider_value_change(int)));

    // QObject::connect(this,SIGNAL(imageSignal(cv::Mat)),this,SLOT(displayMat(cv::Mat)));
    std::cout<<"1-5"<<std::endl;

    // QObject::connect(ui->btnStart,SIGNAL(clicked()),this,SLOT(on_btnStart_clicked()));
    
    ui->btnStart->setCheckable(true);
    ui->btnStart->setStyleSheet("QPushButton {"
                            "color: black;"
                            "border: 2px solid gray;"
                            "}"
                            "QPushButton:checked {"
                            "color: black;"
                            "border: 2px solid red;"
                            // "background: blue;"
                            "}");
    QObject::connect(ui->btnStart,SIGNAL(toggled(bool)),this,SLOT(on_btnStart_toggled()));
 
    std::cout<<"1-6"<<std::endl;

    // QObject::connect(ui->btnSelectCarport,SIGNAL(clicked()),this,SLOT(on_btnSelectCarport_clicked()));
    std::cout<<"1-7"<<std::endl;

    ui->btnPause->setEnabled(false);
    ui->btnPause->setCheckable(true);
    ui->btnPause->setStyleSheet("QPushButton {"
                        "color: black;"
                        "border: 2px solid gray;"
                        "}"
                        "QPushButton:checked {"
                        "color: black;"
                        "border: 2px solid green;"
                        // "background: blue;"
                        "}");
    QObject::connect(ui->btnPause,SIGNAL(toggled(bool)),this,SLOT(on_btnPause_toggled()));
    std::cout<<"1-8"<<std::endl;


    int argc = 0; char **argv = NULL;
    std::cout<<"1-9"<<std::endl;

    ros::init(argc, argv, "avp_ui_node");

    // if (!ros::master::check())
    // {
    //     ROS_INFO("No master started!");
    //     this->close();
    // }
    // ros::start(); // explicitly needed since our nodehandle is going out of scope.

    ros::NodeHandle n;

    traj_sub = n.subscribe<planning_msgs::TrajectoryStamped>("/planning/trajectory_stamped",1, &avp_ui::trajectory_callback, this);

    planning_state_sub = n.subscribe<std_msgs::Int16>("/planning/state", 1, &avp_ui::planning_state_callback, this);
    // locked_carport_sub =n.subscribe<std_msgs::Int16>("/planning/lock_carport_id", 1, &avp_ui::locked_carport_callback, this);
    
    // subscription_parking_slots=n.subscribe<perception_msgs::ParkingSlots>("/perception/parking_slots", 1, &avp_ui::parkingslot_callback, this);      


    button_start_publisher = n.advertise<std_msgs::Int16>("/avp_ui/start_button", 1);
    // select_carport_publisher = n.advertise<std_msgs::Int16>("/avp_ui/selected_carport_id", 1);

    sync_publisher = n.advertise<std_msgs::Int16>("/avp_ui/sync_talker", 1);
    termination_publisher = n.advertise<std_msgs::Int16>("/avp_ui/stop_in_emergency", 1);
    pause_publisher = n.advertise<std_msgs::Int16>("/avp_ui/pause_signal", 1);


    // image_sub = n.subscribe<sensor_msgs::CompressedImage>("/gpsd/detection_image",1, &avp_ui::img_callback, this);
    // localization_sub = n.subscribe<localization_msgs::localization>("/apa_localization",100, &avp_ui::localization_callback, this);
    
    std::cout<<"1-10"<<std::endl;

    // message_filters::Subscriber<sensor_msgs::CompressedImage> img_sub(n, "/gpsd/detection_image", 1);
    // message_filters::Subscriber<localization_msgs::localization> location_sub(n, "/apa_localization", 1);
    // typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::CompressedImage, localization_msgs::localization> MySyncPolicy;
    // // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
    // message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), img_sub, location_sub);

    // // sync.registerCallback(boost::bind(&avp_ui::img_location_callback, this, _1, _2));
    // sync.registerCallback(&avp_ui::img_location_callback, this);

    // location_sub= new message_filters::Subscriber<localization_msgs::localization>(n, "/apa_localization", 300);
    // img_sub  = new message_filters::Subscriber<sensor_msgs::CompressedImage>(n, "/gpsd/detection_image", 1);
   
    // sync = new message_filters::Synchronizer<MySyncPolicy>(MySyncPolicy(300), *img_sub, *location_sub);
    // sync->registerCallback(boost::bind(&avp_ui::img_location_callback,this, _1, _2));
    
    std::cout<<"1-11"<<std::endl;

    


    // ros::spin();

    // 创建一个Qt定时器，每隔100毫秒调用一次timerSlot()函数
    // 由于需要实时收定位，定位发送频率较高，频率设置从配合图片发送频率改为配合定位发送频率，改为10ms。

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    // timer->start(10);
    timer->start(10);
    std::cout<<"1-12"<<std::endl;

}

avp_ui::~avp_ui()
{
    delete ui;
}




