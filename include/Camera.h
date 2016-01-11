#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "JointChain.h"
#include <vector>
#include <string>

class Camera
{
  public:

    Camera();
    ~Camera();

    // Adds an object color to be tracked
    void addObjectToTrack(Object *obj);

    // Captures and processes one frame
    void processFrame();

    // Defines what color to track with focus, default is 0 (the first)
    void setFocusObjectIndex(int focusObjIndex) { this->focusObjIndex = focusObjIndex; }
    int getFocusObjectIndex() { return this->focusObjIndex; }

    // Connects to the robot's neck for pan/tilt tracking
    void setHead(JointChain *head) { this->head = head; }

    // Gets the focus in neck angle
    float getFocusPan() { return focusPan; }
    float getFocusTilt() { return focusTilt; }

    // Gets the focus in normalized neck angle (between 0 and 1)
    float getNormalizedFocusPan();
    float getNormalizedFocusTilt();

  private:

    cv::Mat cameraImage;
    cv::Mat thresholdImage;
    cv::Mat HSVImage;
    VideoCapture capture;
    std::vector<Object *> objectsToTrack;
    std::string intToString(int number);
    unsigned int focusObjIndex;
    void morphOps(Mat &thresh);
    void drawObject(vector<Object> theObjects,Mat &frame, Mat &temp,
                vector< vector<Point> > contours, vector<Vec4i> hierarchy);
    void trackFilteredObject(Object *theObject,Mat threshold,Mat HSV, Mat &cameraFeed);
    JointChain *head;
    float focusPan;
    float focusTilt;

};

#endif

