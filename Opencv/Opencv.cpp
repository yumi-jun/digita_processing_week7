#include <opencv2/highgui.hpp>
using namespace cv;

/*
* Homomorphic Filtering
* 영상의 픽셀 강도는 크게 두가지 영향을 받음
* 1. 조명과 같은 직접적인 광원 빛 i(x,y) -> 천천히 바뀜,, 앞에 있음
* 2. 객체로부터 반사된 빛 r(x,y)
* 디지털 영상은 f(x,y)=i(x,y),r(x,y)로 표현 가능
* 자연 로그를 이용하여 곱을 합으로 표현함.
* 
* 조명의 빛을 없애고 싶음 .. 조명의 빛은 천천히? 바뀔테니.. 위쪽 영향을 빼주자!!
* 
* 디지털 영상의 조명과 반사 성분 각각 필터링하여 출력 영상 g(x,y)를 얻는 것임.
*/
void homomorphicFilter(InputArray input, OutputArray output, float D0, float gammaH, float gammaL)
{
    const Mat& src = input.getMat();
    output.create(input.size(), CV_32FC1);
    Mat dst = output.getMat();
    Mat F,srcLn;
    cv::log(src + 1,srcLn);
    //푸리에 변환,  로그를 취해줌
    dft(srcLn, F, DFT_COMPLEX_OUTPUT);
    float c = 1;
    //필터링
    for (int u = 0; u < F.rows; u++) {
        for(int v=0;v<F.cols;v++){
    
            float D2 = 0;
            if (u < F.rows / 2) { D2 += u * u; }
            else { D2 += (F.rows - u) * (F.rows - u); }
            float D2 = 0;
            if (u < F.cols / 2) { D2 += u * u; }
            else { D2 += (F.cols - u) * (F.cols - u); }

            float D = u * u + v * v;
            
            F.at<float>(u, v) = ((gammaH - gammaL) * (1 - exp(-c * (D * D / D0 / D0))) + gammaL)*F.at<float>(u,v);
        }
    }
    F.at<float>(0, 0) = F.rows * F.cols * 0.5;

   
    imshow("F", F);
    //역푸리에 변환
    idft(F, dst, DFT_REAL_OUTPUT | DFT_SCALE);
    //지수 
    exp(dst, dst);
    dst -= 1;

}
int main()
{
    //Homomorophic Filter
    Mat input = imread("C:/Users/관리자/Desktop/yumi.jpg", 0);
    Mat output;
    //input을 float 값으로 바꿔주고 범위를 1부터 255부터 지정해줌
    input.convertTo(input, CV_32F, 1 / 255.f);

    homomorphicFilter(input, output, 10, 1, 0.4f);

    imshow("output", output);
    waitKey();

}

