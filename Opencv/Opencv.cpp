// Opencv.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <opencv2/highgui.hpp>
using namespace cv;

/*
* Homomorphic Filtering
* 영상의 픽셀 강도는 크게 두가지 영향을 받음
* 1. 조명과 같은 직접적인 광원 빛 i(x,y)
* 2. 객체로부터 반사된 빛 r(x,y)
* 디지털 영상은 f(x,y)=i(x,y),r(x,y)로 표현 가능
* 자연 로그를 이용하여 곱을 합으로 표현함.
* 디지털 영상의 조명과 반사 성분 각각 필터링하여 출력 영상 g(x,y)를 얻는 것임.
*/
void homomorphicFilter(InputArray input, OutputArray output, float D0, float gammaH, float gammaL)
{
    const Mat& src = input.getMat();
    output.create(input.size(), CV_32FC1);
    Mat dst = output.getMat();
    Mat F;

}
int main()
{
    //Homomorophic Filter
    Mat input = imread("C:/Users/관리자/Desktop/yumi.jpg", 0);
    Mat output;
    input.convertTo(input, CV_32F, 1 / 255.f);
    homomorphicFilter(input, output, 15, 1, 0.4f);
    imshow("input", input);
    waitKey();

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
