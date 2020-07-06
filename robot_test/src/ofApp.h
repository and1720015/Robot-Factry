#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxCv.h"

#include <Kinect.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <cstdlib>

#include "ofxGui.h"

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL) {
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void exit();

		IKinectSensor* pSensor;
		HRESULT hResult = S_OK;

		IDepthFrameSource* pDepthSource;
		IDepthFrameReader* pDepthReader;
		IFrameDescription* pDescription;
		ofImage image;
		ofImage binaryImage;
		ofImage edgeImage;

		int width = 0;
		int height = 0;
		unsigned int bufferSize = width * height * sizeof(unsigned short);

		/*	cv::Mat bufferMat(height, width, CV_16UC1);
			cv::Mat depthMat(height, width, CV_8UC1);*/
		cv::Mat bufferMat;
		cv::Mat depthMat;
		cv::Mat rgbMat;
		/*	cv::Mat rgbImage;*/
		cv::Mat binaryMat;
		cv::Mat binaryRgbMat;

		//Gui
		ofxCv::ContourFinder contourFinder;

		ofColor targetColor;

		ofxPanel gui;
		ofParameter<float> minArea, maxArea, threshold;
		ofParameter<bool> trackHs;
		ofParameter<bool> holes;

		ofTrueTypeFont font;
		ofImage image1;
		ofImage image2;
		ofImage image3;
		ofImage image4;
		ofImage image5;
		ofImage image6;
		ofImage image7;
		ofImage image8;
		ofImage image9;

		ofImage back;
		ofImage back_yuka;
		ofImage Side;
		ofImage arm;

		ofImage meter;
		ofImage meter0;
		ofImage meter1;
		ofImage meter2;
		ofImage meter3;
		ofImage meter4;
		ofImage meter5;
		ofImage meter6;
		ofImage hari;

		ofImage paint[5];

		ofSoundPlayer soundink;
		ofSoundPlayer soundmove;
		ofSoundPlayer soundback;

};
