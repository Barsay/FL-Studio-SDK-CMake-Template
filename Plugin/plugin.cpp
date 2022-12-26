#include "plugin.h"


extern "C" __declspec(dllexport) TFruityPlug * _stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
{
    auto plug = new Plugin(Tag, Host);
    return (TFruityPlug *) plug;
};

//constructor
Plugin::Plugin(int Tag, TFruityPlugHost *Host): TCPPFruityPlug(Tag, Host, nullptr){
    Info = &PlugInfo;
    HostTag = Tag;

    ResetParams();
}

void _stdcall Plugin::DestroyObject(){
    //todo
};

int _stdcall Plugin::Dispatcher(int ID, int Index, int Value){
    //todo
    return 0;
};

void _stdcall Plugin::Idle(){
    int a;
    //todo
};

void _stdcall Plugin::SaveRestoreState(IStream *Stream, BOOL Save){
    //todo
};

void _stdcall Plugin::GetName(int Section, int Index, int Value, char *Name){
    //todo
}

int _stdcall Plugin::ProcessParam(int Index, int Value, int RECFlags){
    //todo
    return 0;
}

void _stdcall Plugin::Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length){
    //todo
}

void Plugin::ResetParams() {
    //todo
}
