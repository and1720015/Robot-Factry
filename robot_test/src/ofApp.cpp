#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

int click, a[30], timer ;
//x、yが色
float robx[9], tm, merx, mery, x[100], y[100], h[100], p;
bool moving;
//ofImage img;
//--------------------------------------------------------------
void ofApp::setup() {

	cv::setUseOptimized(true);

	// Sensor
	hResult = GetDefaultKinectSensor(&pSensor);
	if (FAILED(hResult)) {
		std::cerr << "Error : GetDefaultKinectSensor" << std::endl;
		return;
	}

	hResult = pSensor->Open();
	if (FAILED(hResult)) {
		std::cerr << "Error : IKinectSensor::Open()" << std::endl;
		return;
	}

	// Source

	hResult = pSensor->get_DepthFrameSource(&pDepthSource);
	if (FAILED(hResult)) {
		std::cerr << "Error : IKinectSensor::get_DepthFrameSource()" << std::endl;
		return;
	}

	// Reader

	hResult = pDepthSource->OpenReader(&pDepthReader);
	if (FAILED(hResult)) {
		std::cerr << "Error : IDepthFrameSource::OpenReader()" << std::endl;
		return;
	}

	// Description

	hResult = pDepthSource->get_FrameDescription(&pDescription);
	if (FAILED(hResult)) {
		std::cerr << "Error : IDepthFrameSource::get_FrameDescription()" << std::endl;
		return;
	}


	pDescription->get_Width(&width); // 512
	pDescription->get_Height(&height); // 424

	bufferMat = cv::Mat(height, width, CV_16UC1);
	depthMat = cv::Mat(height, width, CV_8UC1);

	// Range ( Range of Depth is 500-8000[mm], Range of Detection is 500-4500[mm] ) 
	unsigned short min = 0;
	unsigned short max = 0;
	pDepthSource->get_DepthMinReliableDistance(&min); // 500
	pDepthSource->get_DepthMaxReliableDistance(&max); // 4500

	//cv::namedWindow("Depth");

	image.allocate(width, height, OF_IMAGE_COLOR);
	binaryImage.allocate(width, height, OF_IMAGE_COLOR);

	//Gui
	gui.setup();
	gui.add(minArea.set("Min area", 0, 1, 100));
	gui.add(maxArea.set("Max area", 133, 1, 500));
	gui.add(threshold.set("Threshold", 199, 0, 255));
	gui.add(holes.set("Holes", false));

	//工場
	font.load("arialbd.ttf", 60);

	back.load("back.png");
	back_yuka.load("back_yuka.png");
	image1.load("robot1.png");
	image2.load("robot2.png");
	image3.load("robot3.png");
	image4.load("robot4.png");
	image5.load("robot5.png");
	image6.load("robot6.png");
	image7.load("robot7.png");
	image8.load("robot8.png");
	image9.load("robot9.png");

	Side.load("Side.png");
	arm.load("arm.png");

	meter.load("meter.png");
	meter0.load("meter0.png");
	meter1.load("meter1.png");
	meter2.load("meter2.png");
	meter3.load("meter3.png");
	meter4.load("meter4.png");
	meter5.load("meter5.png");
	meter6.load("meter6.png");
	hari.load("hari.png");

	paint[0].load("paint1.png");
	paint[1].load("paint2.png");
	paint[2].load("paint3.png");
	paint[3].load("paint4.png");
	paint[4].load("paint5.png");

	soundink.load("ink.mp3");
	soundmove.load("move.mp3");
	soundback.load("back.mp3");


	for (int i = 0;i < 9;i++) {
		robx[i] = -1020 * i;
	}

	tm = 3;

	moving = true;

	soundback.setLoop(true);
	soundback.play();
	soundback.setVolume(0.2);

}

//--------------------------------------------------------------
void ofApp::update() {
	// Frame
	IDepthFrame* pDepthFrame = nullptr;
	hResult = pDepthReader->AcquireLatestFrame(&pDepthFrame);
	if (SUCCEEDED(hResult)) {
		hResult = pDepthFrame->AccessUnderlyingBuffer(&bufferSize, reinterpret_cast<UINT16**>(&bufferMat.data));
		if (SUCCEEDED(hResult)) {
			//深度画像
			bufferMat.convertTo(depthMat, CV_8U, -255.0f / 8000.0f, 255.0f);

			//物体検出
			cv::cvtColor(depthMat, rgbMat, cv::COLOR_GRAY2RGB);
			image.setFromPixels(rgbMat.ptr(), rgbMat.cols, rgbMat.rows, OF_IMAGE_COLOR, false);

			//入力画像、出力画像、閾値(min)、上方向の処理の最大値、使用する閾値の種類
			cv::threshold(depthMat, binaryMat, mouseX, 255, cv::THRESH_BINARY);
			cv::cvtColor(binaryMat, binaryRgbMat, cv::COLOR_GRAY2RGB); //グレースケールから二値化
			binaryImage.setFromPixels(binaryRgbMat.ptr(), binaryRgbMat.cols, binaryRgbMat.rows, OF_IMAGE_COLOR, false);

			//Gui
			contourFinder.setMinAreaRadius(minArea);
			contourFinder.setMaxAreaRadius(maxArea);
			contourFinder.setThreshold(threshold);
			contourFinder.findContours(depthMat);
			contourFinder.setFindHoles(holes);

		}
	}
	SafeRelease(pDepthFrame);


	if (moving == true) {
		//ロボットが流れてく
		for (int i = 0; i < 9; i++) {

			robx[i] = robx[i] + tm;
			robx[i]++;

		}


        //色がついてく
		for (int i = 0;i < click;i++) {
			x[i] = x[i] + tm * 1.35;
		}
          ofResetElapsedTimeCounter();

		}


	for (int i = 0; i < 9; i++) {
		if (robx[i] == ofGetWidth() / 2) {

			timer = ofGetElapsedTimef();
			moving = false;
		}
	}

	if (moving== false && timer > 30 ) {
		moving = true;

	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	//背景の床
	ofSetColor(255, 255, 255);
	back_yuka.draw(0, 0);

	

	//色塗り
		for (int i = 0; i < click; i++) {

			ofPushMatrix();
			ofTranslate(-165, -115);

			paint[a[i]].draw(x[i], y[i]);

			ofPopMatrix();
			ofColor color;
			color.setHsb(h[i], 255, 255);
			ofSetColor(color);
		}
	
	
	ofSetColor(255);
	/*image.draw(0, 0);
	ofSetLineWidth(2);
	contourFinder.draw();*/
	ofNoFill();
	int n = contourFinder.size();
	for (int i = 0; i < n; i++) {
		// 輪郭を包む円
		float circleRadius;
		ofVec3f circleCenter = toOf(contourFinder.getMinEnclosingCircle(i, circleRadius));
		ofDrawCircle(circleCenter, circleRadius);
		//　輪郭を包む円の中心
		ofVec3f center = toOf(contourFinder.getCenter(i));
		ofDrawCircle(center, 2);

		//当たり判定
		if (moving == false) {
			/*色塗り*/
			if ((circleCenter.y > 195 && circleCenter.y < 200) && (circleCenter.x > 130 && circleCenter.x < 280)) { //輪郭の中心が当たったら
				/*if (click < 12) {*/
					h[click] = ofRandom(0, 255);
					x[click] = ofRandom(819, 1111); //860~1578
					y[click] = ofRandom(276, 612); //190~1030
					click++;
				/*}*/

					a[click] = ofRandom(0, 4);
					soundink.setLoop(false);
					soundink.play();
					soundink.setVolume(1);

					
			}
		}
	}
	
	//ロボット
	ofPushMatrix();
	ofTranslate(-100, 0);
	ofSetColor(255, 255, 255);
	for (int i = 0;i < 9;i++) {
		image1.draw(robx[0], ofGetHeight() / 2 - 340);
		image2.draw(robx[1], ofGetHeight() / 2 - 340);
		image3.draw(robx[2], ofGetHeight() / 2 - 340);
		image4.draw(robx[3], ofGetHeight() / 2 - 340);
		image5.draw(robx[4], ofGetHeight() / 2 - 340);
		image6.draw(robx[5], ofGetHeight() / 2 - 340);
		image7.draw(robx[6], ofGetHeight() / 2 - 340);
		image8.draw(robx[7], ofGetHeight() / 2 - 340);
		image9.draw(robx[8], ofGetHeight() / 2 - 340);

		if (robx[i] > 1600) {
			robx[i] = -7650;
			click = 1;
		}
	}
	ofPopMatrix();

	
	/*screenshot
	ofPopMatrix();
	for (int i = 0; i < 9; i++) {
		if (timer > 29) {
			img.grabScreen(720, 90, 1300, 820);
			img.save("screenshot.png");
		}
	}*/

	//背景
	ofSetColor(255, 255, 255);
	back.draw(0, 0);
	meter0.draw(0, 0);
	/*Side.draw(0, 0, ofGetWidth(), ofGetHeight());
	arm.draw(0, 0, ofGetWidth(), ofGetHeight());*/

	//タイマー
	ofPushMatrix();
	//ofScale(2, 2);
	if (timer < 5) {
		meter1.draw(0, 0);
	}
	if (timer < 10) {
		meter2.draw(0, 0);
	}
	if (timer < 15) {
		meter3.draw(0, 0);
	}
	if (timer < 20) {
		meter4.draw(0, 0);
	}
	if (timer < 25) {
		meter5.draw(0, 0);
	}
	if (timer < 30) {
		meter6.draw(0, 0);
	}
	ofPopMatrix();

	meter.draw(0, 0);
	/*gui.draw();*/

	//タイマー
	ofSetColor(0, 0, 0);
	if (moving == false) {
		font.drawString(ofToString(30 - timer), 300, 460);
	}
}





//--------------------------------------------------------------

void ofApp::exit() {
	SafeRelease(pDepthSource);
	SafeRelease(pDepthReader);
	SafeRelease(pDescription);
	if (pSensor) {
		pSensor->Close();
	}
	SafeRelease(pSensor);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {



}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	cout << "x : " << x << " y : " << y << "\n";
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
