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
	config.aperture = 3.0f;
	m_view.setDistance(15);
	config.focalPoint = ofPoint(0, 0, -5);
	config.focalNormal = glm::vec3(0, 0, -1);

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
	m_cameraCenters.reserve(data.nCameras);
	m_cameras.reserve(data.nCameras);
	for (unsigned int y = 0; y < data.cameraRows; y++) // this order because images are loaded in this order
	{
		for (unsigned int x = 0; x < data.cameraCols; x++)
		{
			ofCamera cam;
			cam.setPosition(x * data.baseline, -(y * data.baseline), 0.0f); // -y because we want (top,left):(0,0)
			m_cameraCenters.emplace_back(cam.getPosition());
			m_cameras.emplace_back(cam.getModelViewProjectionMatrix(ofRectangle(0,0,1,1)));
		}
	}

	m_render.setPosition(0, 0, 15);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	m_view.begin();
	ofClear(20);
	ofDrawAxis(10);
	
	for (unsigned int i = 0; i < data.nCameras; i++)
	{
		auto & center = m_cameraCenters[i]; // alias
		auto & image = m_images[i];

		auto & mfd = m_cameras[i]; // 4x4
		//auto rdst = mfd * hkf * pck; // compute projection to camera

		m_shader.begin();
		m_shader.setUniform3f("origin", m_view.getPosition());
		m_shader.setUniform3f("center", center);
		m_shader.setUniform3f("focalPoint", config.focalPoint);
		m_shader.setUniform3f("focalNormal", config.focalNormal);
		m_shader.setUniformMatrix4f("mfd", mfd);
		m_shader.setUniform1f("aperture", config.aperture);
		m_shader.setUniformTexture("texture0", image, 0);
			m_quad.draw();
		m_shader.end();
	}

	m_render.draw();

	m_view.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's' || key == 'S')
	{
		ofSaveScreen("screenshots/" + ofGetTimestampString() + ".png");
	}
	if (key == ' ')
	{
		m_shader.load("shader/lightfield");
	}

	if (key == OF_KEY_LEFT)
	{
		config.aperture -= 0.1f;
	}
	if (key == OF_KEY_RIGHT)
	{
		config.aperture += 0.1f;
	}
	if (key == OF_KEY_UP)
	{
		config.focalPoint.z -= 10.0f;
	}
	if (key == OF_KEY_DOWN)
	{
		config.focalPoint.z += 10.0f;
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
