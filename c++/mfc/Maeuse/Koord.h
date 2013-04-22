class CKoord : public CObject {
	DECLARE_SERIAL(CKoord)
public:
	CKoord();
	CKoord(int x_koord, int y_koord);
	int x;
	int y;
	virtual void Serialize(CArchive &ar);
};
