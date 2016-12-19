#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    cv::VideoCapture cap;
    cap.open(0);
    cv::waitKey(1000);
    if(!cap.isOpened())
    {
        cout <<"Camer break!" <<endl;
        return -1;
    }

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    cv::Mat  frame;
    cap >>frame;



    cv::Mat  intrinsic_matrix = cv::Mat(3,3,CV_64FC1);
    intrinsic_matrix =  (cv::Mat_<double>(3,3) <<373.1612305033341,0,915.0542831575406,0,373.2469226288663,526.4727331036754,0,0,1);    /*****    摄像机内参数矩阵    ****/
    cv::Mat distortion_coeffs=(cv::Mat_<double>(4,1) <<-0.02245761619802443,
    -0.01788205446531621,
    0.02958457189859384,
    -0.0289088254709169);     /* 摄像机的4个畸变系数：k1,k2,k3,k4*/
    cv::Mat R = cv::Mat::eye(3,3,CV_32F);
    cv::Size image_size = frame.size();

    cv::Mat mapx = cv::Mat::zeros(image_size,CV_32FC1);
    cv::Mat mapy = cv::Mat::zeros(image_size,CV_32FC1);


//    intrinsic_matrix.at<double>(0,0) =  373.1612305033341;
//    intrinsic_matrix.at<double>(0,2) =  915.0542831575406;
//    intrinsic_matrix.at<double>(1,1) =  373.2469226288663;
//    intrinsic_matrix.at<double>(1,2) =  526.4727331036754;
//    intrinsic_matrix.at<double>(2,2) =  1;


//    distortion_coeffs =  {-0.0224576, -0.0178821, 0.0295846, -0.0289088};

    cout <<"intrinsic_matrix" <<intrinsic_matrix <<endl;
    cout <<"distortion_coeffs:" <<distortion_coeffs <<endl;


    cv::fisheye::initUndistortRectifyMap(intrinsic_matrix,distortion_coeffs,R,intrinsic_matrix,image_size,CV_32FC1,mapx,mapy);


   while(1)
   {
       cap >>frame;
       cv::imshow("srcImage",frame);

       cv::Mat dstImage = frame.clone();
       cv::remap(frame,dstImage,mapx, mapy, cv::INTER_LINEAR);
       cv::imshow("dstImage",dstImage);

//       string imageFileName;
//       std::stringstream StrStm;
//       StrStm<<1;
//       StrStm>>imageFileName;
//       imageFileName += "_d.jpg";
//       imwrite(imageFileName,dstImage);

       cv::waitKey(10);
   }

    cv::waitKey(0);
    return 0;
}
