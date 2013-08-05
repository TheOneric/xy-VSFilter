

class XyAutoLoaderDummyInputPin: public CBaseInputPin
{
public:
    XyAutoLoaderDummyInputPin(
        CBaseFilter *pFilter,
        CCritSec *pLock,
        HRESULT *phr,
        LPCWSTR pName);

    HRESULT CheckMediaType(const CMediaType *);
};

[uuid("6b237877-902b-4c6c-92f6-e63169a5166c")]
class XySubFilterAutoLoader : public CBaseFilter
{
public:
    XySubFilterAutoLoader(LPUNKNOWN punk, HRESULT* phr, const GUID& clsid = __uuidof(XySubFilterAutoLoader));
    virtual ~XySubFilterAutoLoader();

    DECLARE_IUNKNOWN;

    //CBaseFilter
    CBasePin* GetPin(int n);
    int GetPinCount();
    STDMETHODIMP JoinFilterGraph(IFilterGraph* pGraph, LPCWSTR pName);

    STDMETHODIMP QueryFilterInfo(FILTER_INFO* pInfo);

    bool ShouldWeAutoLoad(IFilterGraph* pGraph);
public:
    static HRESULT GetMerit( const GUID& clsid, DWORD *merit );
protected:
    CCritSec m_pLock;
    XyAutoLoaderDummyInputPin * m_pin;

    int                 m_load_level;
    bool                m_load_external;
    bool                m_load_web;
    bool                m_load_embedded;
    CString             m_load_exts;
    CAtlArray<CString>  m_paths;
};