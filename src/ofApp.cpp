#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // load all the images
    ofLog() << "Gathering images...";
    ofDirectory dir1;
    ofDirectory dir2;
    ofDirectory dir3;
    ofDirectory dir4;
    ofDirectory dir5;

    t=0;
    //
    int nFiles = dir1.listDir(ofToDataPath("/Users/user1/Pictures/dataZ/hymenoptera_data/val/ants"));
    
    if(nFiles) {
        // 0, dir.size(), i++
        for(int i=0; i < dir1.size(); i++) {
            if (i % 10 == 0) ofLog() << " - loading image "<<i<<" / "<< dir1.size();
            string filePath1 = dir1.getPath(i);
            images.push_back(ofImage());
            images.back().load(filePath1);
            imgType[t] = 0; // ********************
            imgPath[t] = filePath1;  // pww, 211208
            t++;
        }// for
    }// if

    
    int nFiles2 = dir2.listDir(ofToDataPath("/Users/user1/Pictures/dataZ/hymenoptera_data/val/bees"));
    
    if(nFiles2) {
        for(int i=0; i< dir2.size(); i++) {
            if (i % 10 == 0) ofLog() << " - loading image "<<i<<" / "<< dir2.size();
            string filePath2 = dir2.getPath(i);
            images.push_back(ofImage());
            images.back().load(filePath2);
            imgType[t] = 1; // ********************
            imgPath[t] = filePath2;  //pww, 211208
            t++;
        }
    }
    
    // setup ofxCcv
    ccv.setup("image-net-2012.sqlite3");

    // encode all of the images with ofxCcv
    ofLog() << "Encoding images...";
    
    for (int i=0; i<images.size(); i++) {
        if (i % 10 == 0) ofLog() << " - encoding image "<<i<<" / "<< images.size();
        vector<float> encoding = ccv.encode(images[i], ccv.numLayers()-1);
        encodings.push_back(encoding);
    }
    
    // Save encodings vector to file ====================
    // save the encodings to a file
        ofBuffer buffer;
        for (int i = 0; i < encodings.size(); i++) {
            vector<float> encoding = encodings[i];
            for (int j = 0; j < encoding.size(); j++) {
                buffer.append(ofToString(encoding[j]) + " ");
            }
            buffer.append("\n");
        }
        ofFile file("encodings_NG_OK.txt", ofFile::WriteOnly);
        file << buffer;


    // run t-SNE and load image points to imagePoints
    //ofLog() << "Run t-SNE on images";
    //imagePoints = tsne.run(encodings, 2, 25, 0.1, true);
    //
    // run t-SNE and load image points to imagePoints
    ofLog() << "Run t-SNE on images";
    imagePoints = tsne.run(encodings, 3, 25, 0.1, true); // 2차원에서 3차원으로 변경


    // make the images the same size
    for (int i=0; i< images.size(); i++) {
    images[i].resize(100 * images[i].getWidth() / images[i].getHeight(), 100);
    }

    // setup gui
    gui.setup();
    // 0.1
    // scale.set("", init, start, stop)
    gui.add(scale.set("scale", 0.7, 0.0, 10.0));
    // 0.8
    gui.add(imageSize.set("imageSize", 0.1, 0.0, 2.0));
    
    // setup camera
    cam.setDistance(1000);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(100, 100, 100);
    
    cam.begin();

    // Rotation factor based on time
    float rotation = ofGetElapsedTimef() * 30;
    
    ofPushMatrix();
    ofRotateYDeg(rotation);

    // 이미지 디스플레이
    for (int i=0; i< imagePoints.size(); i++)
    {
        float x = ofMap(imagePoints[i][0], 0, 1, 0, scale * ofGetWidth());
        float y = ofMap(imagePoints[i][1], 0, 1, 0, scale * ofGetHeight());
        float z = ofMap(imagePoints[i][2], 0, 1, 0, scale * ofGetHeight()); // add third dimension

        ofSetColor(255,255,255);
        images[i].draw(x, y, z, imageSize * images[i].getWidth(), imageSize * images[i].getHeight());
    }

    ofNoFill();
    for (int i=0; i< imagePoints.size(); i++)
    {
        float x = ofMap(imagePoints[i][0], 0, 1, 0, scale * ofGetWidth());
        float y = ofMap(imagePoints[i][1], 0, 1, 0, scale * ofGetHeight());
        float z = ofMap(imagePoints[i][2], 0, 1, 0, scale * ofGetHeight()); // add third dimension

        // Draw Border Based on Image Type
        switch(imgType[i])
        {
            case 0:
                ofSetColor(0,0,255);
                break;
            case 1:
                ofSetColor(0,255,0);
                break;
        }

        ofSetLineWidth(2);
        ofDrawRectangle(x, y, z, imageSize * images[i].getWidth(), imageSize * images[i].getHeight());
    }

    ofPopMatrix();
    
    cam.end();
    gui.draw();
}