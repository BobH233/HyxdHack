//get dir
using namespace std;
#include <fstream>
#include <time.h> 
#include <stdio.h> 
char dlldir[320];

char *GetDirectoryFile(char *filename)
{
	static char path[320];
	strcpy_s(path, dlldir);
	strcat_s(path, filename);
	return path;
}

void InitLog() {
	ofstream logfile("D:\\log.txt");
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
	logfile << tmp << " By BobH " << endl;
	logfile.close();
}
//log
void Log(const char *fmt, ...)
{
	if (!fmt)	return;

	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	ofstream logfile("D:\\log.txt", ios::app);
	if (logfile.is_open() && text)	logfile << text << endl;
	logfile.close();
}
//read Setting (lab)
int ReadSettingFile() {
	ifstream logfile("D:\\set.txt");
	int value;
	logfile >> value;
	return value;
}
//==========================================================================================================================
//read min id
int ReadNumMin() {
	ifstream logfile("D:\\num.txt");
	int min;
	logfile >> min;
	return min;
}
//read max id
int ReadNumMax() {
	ifstream logfile("D:\\num.txt");
	int min,max;
	logfile >> min >> max;
	return max;
}

//generate shader func
HRESULT GenerateShader(ID3D11Device* pD3DDevice, ID3D11PixelShader** pShader, float r, float g, float b)
{
	char szCast[] = "struct VS_OUT"
		"{"
		" float4 Position : SV_Position;"
		" float4 Color : COLOR0;"
		"};"

		"float4 main( VS_OUT input ) : SV_Target"
		"{"
		" float4 fake;"
		" fake.a = 1.0f;"
		" fake.r = %f;"
		" fake.g = %f;"
		" fake.b = %f;"
		" return fake;"
		"}";
	ID3D10Blob* pBlob;
	char szPixelShader[1000];

	sprintf_s(szPixelShader, szCast, r, g, b);

	ID3DBlob* d3dErrorMsgBlob;

	HRESULT hr = D3DCompile(szPixelShader, sizeof(szPixelShader), "shader", NULL, NULL, "main", "ps_4_0", NULL, NULL, &pBlob, &d3dErrorMsgBlob);

	if (FAILED(hr))
		return hr;

	hr = pD3DDevice->CreatePixelShader((DWORD*)pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pShader);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

//==========================================================================================================================

//wh
char *state;
ID3D11RasterizerState * rwState;
ID3D11RasterizerState * rsState;

enum eDepthState
{
	ENABLED,
	DISABLED,
	READ_NO_WRITE,
	NO_READ_NO_WRITE,
	_DEPTH_COUNT
};

ID3D11DepthStencilState* myDepthStencilStates[static_cast<int>(eDepthState::_DEPTH_COUNT)];

void SetDepthStencilState(eDepthState aState)
{
	pContext->OMSetDepthStencilState(myDepthStencilStates[aState], 1);
}

//==========================================================================================================================
