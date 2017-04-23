#pragma once

#include "ofMain.h"

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
		
private:
	vector<ofImage> m_images;
	vector<glm::mat4> m_cameras;
	vector<ofPoint> m_cameraCenters;
	ofTexture m_weight;
	ofVboMesh m_quad;
	ofShader m_shader;
	ofEasyCam m_view;

	ofCamera m_render;

	struct Data
	{
		unsigned int cameraCols;
		unsigned int cameraRows;
		unsigned int nCameras;
		float baseline;
	};
	Data data;

	struct Config
	{
		float aperture;
		ofPoint focalPoint;
		glm::vec3 focalNormal;
	};
	Config config;
};
