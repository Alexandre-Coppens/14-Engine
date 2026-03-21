#include "CameraManager.h"

#include "DebugMemoryLeakCatcher.h"
#include "Engine/3D/Camera.h"
#include "Engine/Utilitaries/Log.h"

Uint8 CameraManager::mCurrentCamera ;
std::vector<Camera*> CameraManager::mCameraList;

CameraManager::CameraManager()
{
    DEBUGAddClass("CameraManager");
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
    for (Camera* camera : mCameraList)
    {
        camera = nullptr;
    }
    mCameraList.clear();
    DEBUGRemoveClass("CameraManager");
}
