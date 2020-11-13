#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int n = ofMap(ofNoise(39, ofGetFrameNum() * 0.005), 0, 1, 0, 100);
	int len = 300;
	bool color_flag = true;
	for (int z = len * -0.5; z < len * 0.5; z += 60) {

		for (int param_start = n; param_start < n + 100; param_start += 5) {

			ofMesh mesh, frame;
			frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

			for (int param = param_start; param <= param_start + 5; param++) {

				auto side_1 = glm::vec3(this->make_point(len, param), z + 30);
				auto side_2 = glm::vec3(this->make_point(len, param), z - 30);

				mesh.addVertex(side_1);
				mesh.addVertex(side_2);

				mesh.addColor(color_flag ? ofColor(79, 172, 135) : ofColor(39));
				mesh.addColor(color_flag ? ofColor(79, 172, 135) : ofColor(39));

				frame.addVertex(side_1);
				frame.addVertex(side_2);

				frame.addColor(ofColor(39));
				frame.addColor(ofColor(39));

				int index = mesh.getNumVertices() - 1;
				if (param > param_start) {

					mesh.addIndex(index); mesh.addIndex(index - 2); mesh.addIndex(index - 3);
					mesh.addIndex(index); mesh.addIndex(index - 1); mesh.addIndex(index - 3);

					frame.addIndex(index); frame.addIndex(index - 2);
					frame.addIndex(index - 1); frame.addIndex(index - 3);
				}
			}

			mesh.draw();

			frame.addIndex(0); frame.addIndex(1);
			frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);
			frame.drawWireframe();

			color_flag = !color_flag;

		}

		n += 5;
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}