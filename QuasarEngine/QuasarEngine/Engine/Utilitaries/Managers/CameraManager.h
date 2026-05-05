#pragma once
#include <vector>

class Camera;
class CameraManager
{
protected:
    static uint8_t mCurrentCamera;
    static std::vector<Camera*> mCameraList;

public:
    static void setCurrentCamera(const int _cameraIndex) {mCurrentCamera = (static_cast<int>(_cameraIndex) >= static_cast<int>(mCameraList.size()) ? 0 : static_cast<uint8_t>(_cameraIndex));}

private:
public:
    CameraManager();
    ~CameraManager() = default;

    static void UpdateCurrentCamera();

    static void AddCamera(Camera* _camera);
    static void RemoveCamera(Camera* _camera);

    static void Close();
};
