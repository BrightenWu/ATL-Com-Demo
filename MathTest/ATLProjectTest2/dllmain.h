// dllmain.h: 模块类的声明。

class CATLProjectTest2Module : public ATL::CAtlDllModuleT< CATLProjectTest2Module >
{
public :
	DECLARE_LIBID(LIBID_ATLProjectTest2Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECTTEST2, "{0c78c5b3-e4a2-45af-b917-4dcaaf76267a}")
};

extern class CATLProjectTest2Module _AtlModule;
