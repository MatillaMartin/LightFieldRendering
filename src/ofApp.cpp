#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(ofLogLevel::OF_LOG_VERBOSE);
	ofLogToConsole();

	// hardcoded data.. could be loaded meh..
	data.cameraCols = 9;
	data.cameraRows = 9;
	data.nCameras = data.cameraCols * data.cameraRows;
	data.baseline = 6.0f; // in mm

	// hardcoded options
	config.aperture = 2.5f;
	m_view.setDistance(15);

	// load images
	ofDirectory dir(".");
	dir.allowExt("png");
	dir.listDir();
	auto imagesPath = dir.getFiles();

	assert(data.nCameras == imagesPath.size()); // just checking

	m_images.reserve(data.nCameras);
	for (const auto & imagePath : imagesPath)
	{
		m_images.emplace_back(imagePath.getFileName());
	}

	// create quad
	m_quad.addVertex(ofDefaultVertexType(glm::vec3(0, 1, 0)));
	m_quad.addVertex(ofDefaultVertexType(glm::vec3(1, 1, 0)));
	m_quad.addVertex(ofDefaultVertexType(glm::vec3(1, 0, 0)));
	m_quad.addVertex(ofDefaultVertexType(glm::vec3(0, 0, 0)));

	m_quad.addTexCoord(ofDefaultTexCoordType(0, 0));
	m_quad.addTexCoord(ofDefaultTexCoordType(1, 0));
	m_quad.addTexCoord(ofDefaultTexCoordType(1, 1));
	m_quad.addTexCoord(ofDefaultTexCoordType(0, 1));

	m_quad.addIndex(0);
	m_quad.addIndex(1);
	m_quad.addIndex(2);
	m_quad.addIndex(0);
	m_quad.addIndex(2);
	m_quad.addIndex(3);

	// load shader
	m_shader.load("shader/lightfield");

	// set camera centers
	for (unsigned int y = 0; y < data.cameraRows; y++) // this order because images are loaded in this order
	{
		for (unsigned int x = 0; x < data.cameraCols; x++)
		{
			m_cameraCenters.emplace_back(x * data.baseline, -(y * data.baseline), 0.0f); // -y because we want (top,left):(0,0)
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	m_view.begin();
	ofClear(0);
	ofDrawAxis(10);
	ofSetColor(127);
	for (unsigned int i = 0; i < data.nCameras; i++)
	{
		auto & center = m_cameraCenters[i]; // alias
		auto & image = m_images[i];
		m_shader.begin();
		m_shader.setUniform3f("center", center);
		m_shader.setUniform1f("aperture", config.aperture);
		m_shader.setUniformTexture("texture", image, 5);
			m_quad.draw();
		m_shader.end();
	}
	m_view.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's' || key == 'S')
	{
		ofSaveScreen("screenshots/" + ofGetTimestampString() + ".png");
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
