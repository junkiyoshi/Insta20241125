#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 120;
	int hue_base = 0;
	for (int x = span * 1; x <= ofGetWindowWidth() - span * 1; x += span) {

		for (int y = span * 1; y <= ofGetWindowHeight() - span * 1; y += span) {

			auto seed = ofRandom(1000);
			vector<glm::vec2> vertices;

			for (int i = 0; i < 200; i++) {

				auto center = glm::vec2(x, y);
				auto radius = 80;

				for (int draw_radius = radius; draw_radius > 0;) {

					auto tmp_radius = draw_radius;
					draw_radius -= 10;

					auto deg = ofMap(ofNoise(seed, draw_radius, (ofGetFrameNum() + i) * 0.005), 0, 1, -360 * 3, 360 * 3);
					auto center_radius = tmp_radius - draw_radius;
					center = center + glm::vec2(center_radius * cos(deg * DEG_TO_RAD), center_radius * sin(deg * DEG_TO_RAD));

					if (draw_radius == 10) {

						vertices.push_back(center);
					}
				}

				ofColor color;
				for (int k = 1; k < vertices.size(); k++) {

					color.setHsb((hue_base + ofGetFrameNum() + k) % 255, 100, ofMap(k, 1, vertices.size(), 39, 255));
					ofSetColor(color);

					ofDrawLine(vertices[k - 1], vertices[k]);
				}
			}

			hue_base += 51;
		}
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}