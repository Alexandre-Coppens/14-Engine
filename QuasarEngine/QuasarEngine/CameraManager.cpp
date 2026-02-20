#include "CameraManager.h"

#include "Camera.h"
#include "Log.h"

Uint8 CameraManager::mCurrentCamera ;
std::vector<Camera*> CameraManager::mCameraList;

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
    Close();
}

void CameraManager::UpdateCurrentCamera()
{
    if (mCameraList.empty())
    {
        Log::Error(LogType::Video, "CameraManager::CameraList is empty");
        return;
    }
    mCameraList[mCurrentCamera]->UpdateCameraView();
}

void CameraManager::AddCamera(Camera* _camera)
{
    mCameraList.push_back(_camera);
}

void CameraManager::RemoveCamera(Camera* _camera)
{
    mCameraList.erase(std::remove(mCameraList.begin(), mCameraList.end(), _camera), mCameraList.end());
}

void CameraManager::Close()
{
    for (Camera* c : mCameraList)
    {
        c = nullptr;
    }
    mCameraList.clear();
}
