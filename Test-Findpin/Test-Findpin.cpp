// Test-Findpin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <dshow.h>

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

// set this to the OBS Virtual Camera GUID
GUID CLSID_OBS_FILTER_GUID = { 0xA3FCE0F5, 0x3493, 0x419F, 0x95, 0x8A, 0xAB, 0xA1, 0x25, 0x0E, 0xC2, 0x0B};

int main()
{
    HRESULT hr;
    hr = CoInitialize(NULL);
    if (hr == S_OK) {
        IBaseFilter* pFilter;
            
        hr = CoCreateInstance(CLSID_OBS_FILTER_GUID, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFilter));
        if (hr == S_OK) {
            IPin* pPin;
                
            // https://docs.microsoft.com/hr-hr/windows/win32/api/strmif/nf-strmif-ibasefilter-findpin

            // correct name, returns: S_OK
            hr = pFilter->FindPin(L"Output Pin", &pPin);
            std::cout << "test 1 FindPin result:" << hr << "\n";
            if (hr == S_OK) {
                SafeRelease(&pPin);
            }

            // wrong name, returns: VFW_E_NOT_FOUND
            hr = pFilter->FindPin(L"orange juice Pin", &pPin);
            std::cout << "test 2 FindPin result:" << hr << "\n";
            if (hr == S_OK) {
                SafeRelease(&pPin);
            }

            // name null, returns: E_POINTER
            hr = pFilter->FindPin(NULL, &pPin);
            std::cout << "test 3 FindPin result:" << hr << "\n";
            if (hr == S_OK) {
                SafeRelease(&pPin);
            }

            // pointer null, returns: E_POINTER
            hr = pFilter->FindPin(L"Output Pin", NULL);
            std::cout << "test 4 FindPin result:" << hr << "\n";
            if (hr == S_OK) {
                SafeRelease(&pPin);
            }

            SafeRelease(&pFilter);
        }
        CoUninitialize();
    }
}
