#pragma once
#include <SDL_stdinc.h>
#include <vector>

class Camera;
class CameraManager
{
protected:
    static Uint8 mCurrentCamera;
    static std::vector<Camera*> mCameraList;

public:
    static void setCurrentCamera(const int _cameraIndex) {mCurrentCamera = (static_cast<int>(_cameraIndex) >= mCameraList.size() ? 0 : _cameraIndex);};

private:
public:
    CameraManager();
    ~CameraManager();

    static void UpdateCurrentCamera();

    static void AddCamera(Camera* _camera);
    static void RemoveCamera(Camera* _camera);

    static void Close();
};
