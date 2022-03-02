#include "FlameUI.h"
#include "Frame.h"
#include "Label.h"
#include "Button.h"
#include "Image.h"
#include "Scroller.h"
#include "ScrollView.h"
#include "CheckBox.h"
#include "Toggle.h"
#include "RadioButton.h"
#include "TextEditor.h"

#include "ISerializer.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include "Manager.h"
#include "LinearPlacer.h"
#include "SectionBar.h"
#include "SheetView.h"
#include "MenuFrame.h"
#include "DockProvider.h"
#include "SeperatorHandle.h"
#include "ImGuiCanvas.h"

#include "resource2.h"

enum TYPEDENUM :char
{

};
//Manager libm(L"I:\\FlameUI\\db");
Manager libm;

int main()
{
	//int a;
	//wcout.imbue(locale("chs"));
	//Manager bm(L"F:\\Learn\\FlameUI\\db");
	//bm.AMBookInfo(BookInfo("0000000000000", 0, L"高等数学", L"高等教育出版社", L"不知道", 2699)); //25978596498929
	//bm.AMBookInfo(BookInfo("0000000000233", 0, L"Gaazar", L"publisherrr", L"IDK", 2333)); //25978596498931
	//bm.AMBookInstance(Book(25978596498929)); //25978599014307
	//bm.AMBookInstance(Book(25978596498931)); //25978599014308
	//bm.AMBookInstance(Book(25978596498931)); //25978599014309
	//bm.AMBookInstance(Book(25978596498931)); //25978599014310
	/*tm bt;
	bt.tm_year = 1998 - 1900;
	bt.tm_mon = 0;
	bt.tm_mday = 4;
	bt.tm_hour = 0;
	bt.tm_min = 0;
	bt.tm_sec = 1;
	bt.tm_isdst = -1;
	cout << mktime(&bt);
	bm.AMBorrower(Borrower(L"Gaazar", mktime(&bt), L"202021091000", SEX_MALE)); //25978644211603
	bt.tm_mon = 6;
	bt.tm_mday = 18;
	bm.AMBorrower(Borrower(L"Trim", mktime(&bt), L"202021091200", SEX_FEMALE)); //25978644211604
	bm.Commit();*/
	//bm.NewLent(25978599014308, { 25978644211604 , time(0),30 * 24 * 60 ,0 });
	//bm.NewLent(25978599014309, { 25978644211603 , time(0),30 * 24 * 60 ,0 });
	//bm.Commit();
	//cin >> a;
	WinMain(0, 0, nullptr, 0);
	return 0;
}



using namespace FlameUI;
using namespace std;

TextEditor* e_db;
SheetView* sv_db;
SheetView* sv_db_info;
SheetView* sv_detl;
ScrollView* srv_det;
CheckBox* ckb_filters_db[6];
Toggle* tg_fold;
TextEditor* te_dvs[10];
Label* l_dv_id;
Panel* pnl_infedr;

struct
{
	TextEditor* e_db;
	SheetView* sv_br;
	SheetView* sv_detl;
	CheckBox* ckb_filters_db[6];
	Toggle* tg_edit;
	ScrollView* srv_editor;
	TextEditor* te_dvs[7];
	Label* l_id;

} bor;

struct
{
	TextEditor* e_db;
	SheetView* sv_br;
	SheetView* sv_detl;
	CheckBox* ckb_filters_db[6];
	ScrollView* srv_editor;
	TextEditor* te_dvs[7];
	Label* l_id;

} rec;
struct
{
	Label* l_bkinf;
	TextEditor* te_bkid;

	Label* l_brinf;
	TextEditor* te_brpid;
	Label* l_bill;

} bl;


void InitInstance(View* pnl);
void InitLentret(View* pnl);
void InitBorrower(View* pnl);
void InitRecord(View* pnl);
void Test()
{
	Frame f({ 1280,720 });

	Label l(&f, L"Label Text\nUnicode:我😀😁😂🤣🤣\nButton\nasdasdasfasG给哇嘎哇给啊尬舞尬舞");
	l.Position({ 300,50 });
	Button b(&f);
	Label ll(&b, L"Button0");
	auto path = L"D:\\Picture\\a_cccp.png";
	Image img(&f);
	img.Content(path);
	img.Position({ 20,250 });
	img.Size({ 100,100 });
	ll.Coord(COORD_CENTER, COORD_CENTER);
	//ll.Position({ 20,10 });
	b.Position({ 300,300 });

	ScrollView p(&f);
	p.Position({ 550,50 });
	p.Size({ 400,600 });
	p.Content()->Size({ 300, 300 });
	//p.Content()->SizeMode(SIZE_MODE_CHILDREN, SIZE_MODE_CHILDREN);
	Label lp(p.Content(), L"Label in Panel.");
	Button bp(p.Content());
	bp.Size({ 120,32 });
	bp.Position({ 50,50 });
	Label bpl(&bp, L"Panel Label");
	bpl.Coord(COORD_CENTER, COORD_CENTER);

	CheckBox cb(p.Content());
	cb.Position({ 200, 15 });
	Toggle tg(p.Content());
	tg.Position({ 200, 40 });
	RadioButton rb(p.Content());
	rb.Position({ 200, 65 });
	RadioButton rb2(p.Content());
	rb2.Position({ 230, 65 });

	TextEditor te(p.Content());
	te.Size({ 300,300 });
	te.Position({ 50, 100 });

	Scroller s(&f);
	s.Position({ 500,50 });
	f.Show();
	f.MainLoop();

}

wstring timefmt(time_t tt, bool hms = true)
{
	if (tt < 0) tt = 0;
	tm* t = localtime(&tt);
	int year = t->tm_year + 1900;
	int mon = t->tm_mon + 1;
	int day = t->tm_mday;
	int hour = t->tm_hour;
	int min = t->tm_min;
	int sec = t->tm_sec;

	wostringstream tmp;
	tmp << year << L"-" << mon << L"-" << day;
	if (hms) tmp << L" " << hour << L":" << min << L":" << sec;
	wstring wtime = tmp.str();
	return wtime;
}
void split(const wstring& s, vector<wstring>& tokens, const wstring& delimiters = L" ")
{
	wstring::size_type lastPos = s.find_first_not_of(delimiters, 0);
	wstring::size_type pos = s.find_first_of(delimiters, lastPos);
	while (wstring::npos != pos || wstring::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}
bool less(const BookInfo*& a, const BookInfo*& b)
{
	return a->Instances().size() < b->Instances().size();
}
bool less(const Book*& a, const Book*& b)
{
	return false;
	//return a->Instances().size() < b->Instances().size();
}

void cb_pc_anim(float p, WPARAM w, LPARAM l)
{
	float fx = Easings::ExpoOut(p);
	((View*)(w))->Alpha(1 - fx);
	((View*)(l))->Alpha(fx);
	((View*)(w))->Scale({ 0.95f + fx * 0.05f ,0.95f + fx * 0.05f });
	((View*)(l))->Scale({ 1 + fx * 0.05626f ,1 + fx * 0.05626f });
	if (p >= 1)
	{
		((View*)(w))->disabled = false;
	}
}
LRESULT cb_tg_fd_vc(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	sv_db->disabled = true;
	sv_db_info->disabled = true;
	if (tg_fold->Checked())
	{
		Animate(&cb_pc_anim, 800, (WPARAM)sv_db_info, (LPARAM)sv_db);
		Animate(&cb_pc_anim, 800, (WPARAM)srv_det, (LPARAM)pnl_infedr);
	}
	else
	{
		Animate(&cb_pc_anim, 800, (WPARAM)sv_db, (LPARAM)sv_db_info);
		Animate(&cb_pc_anim, 800, (WPARAM)pnl_infedr, (LPARAM)srv_det);
	}
	return 0;
}
LRESULT cb_sb_sc(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	//OutputDebugStringA("CHANGE\n");
	if (wparam && lparam)
	{
		((View*)wparam)->disabled = true;
		((View*)lparam)->disabled = true;
		((View*)wparam)->SendEvent(FE_ONSHOW, 0, 0);
		view->value = Animate(&cb_pc_anim, 800, wparam, lparam, view->value);
	}
	return 0;
}
LRESULT cb_sv_s(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (tg_fold->Checked())
	{
		auto i = sv_db_info->Selection(wparam, 0);
		l_dv_id->Content(i->disp);
		BookInfo* bi = (BookInfo*)i->val;
		te_dvs[0]->Content(bi->name);
		te_dvs[1]->Content(bi->author);
		te_dvs[2]->Content(bi->publisher);
		te_dvs[3]->Content(bi->GetISBN());
		te_dvs[4]->Content(bi->catagory);
		te_dvs[5]->Content(to_wstring(bi->price / 100.0f));
		te_dvs[6]->Content(to_wstring(bi->lentLimitation / 24 / 60 / 60.0f));
		te_dvs[7]->Content(to_wstring(bi->priceOverduePd / 100.0f));

	}
	else
	{
		auto i = sv_db->Selection(wparam, 0);
		sv_detl->Clear();
		Book* b = (Book*)i->val;
		for (auto n = b->lents.rbegin(); n != b->lents.rend(); ++n)
		{
			auto br = libm.GetBorrower(n->borrower);
			wstring time = L"待还";
			if (n->returntime) time = timefmt(n->returntime, false);
			if (br)
				sv_detl->AddRow({
					{br->name,0},
					{timefmt(n->lentout,false),0},
					{time,0}
					});

		}
	}
	return 0;
}
LRESULT cb_db_s_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	int fts = 0;
	for (int i = 0; i < 6; i++)
		if (ckb_filters_db[i]->Checked())
			fts = fts | ckb_filters_db[i]->value;
	wstring keyw(e_db->Content());

	auto c = libm.SelectInstance(keyw, (KFILTER)fts);
	RunInUIThread([c]() {
		sv_db->Clear();
		for (auto i = c.begin(); i != c.end(); i++)
		{
			wstring state = L"在库";
			for (auto n = (*i)->lents.begin(); n != (*i)->lents.end(); n++)
			{
				if (n->returntime == 0)
				{
					state = L"借出 " + timefmt(n->lentout, false);
					break;
				}
			}
			sv_db->AddRow({
				{to_wstring((*i)->identifier()),(*i)},
				{(*i)->info()->name,0},
				{(*i)->info()->author,0},
				{(*i)->info()->publisher,0},
				{(*i)->info()->GetISBN(),0},
				{(*i)->info()->catagory,0},
				{state,0}
				});
		}

		});
	auto r = libm.SelectInfo(keyw, (KFILTER)fts);
	RunInUIThread([r]() {
		sv_db_info->Clear();
		for (auto i = r.begin(); i != r.end(); i++)
		{
			sv_db_info->AddRow({
				{to_wstring((*i)->identifier()),(*i)},
				{(*i)->name,0},
				{(*i)->author,0},
				{(*i)->publisher,0},
				{(*i)->GetISBN(),0},
				{(*i)->catagory,0},
				{to_wstring((*i)->Instances().size()),0}
				});
		}

		});
	return 0;
}
LRESULT cb_db_addi_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (sv_db_info->Selected() >= 0)
	{
		BookInfo* bi = (BookInfo*)sv_db_info->Selection(sv_db_info->Selected(), 0)->val;
		int cnt = stoi(te_dvs[8]->Content());
		while (cnt-- > 0)
			libm.AMBookInstance(Book(*bi));

		e_db->Content(to_wstring(bi->identifier()));
		cb_db_s_clk(0, 0, 0, 0);
		sv_db_info->Selected(0);
		cb_sv_s(0, 0, 0, 0);
	}
	return 0;
}
LRESULT cb_db_modify_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (sv_db_info->Selected() >= 0)
	{
		if (te_dvs[3]->Content().length() != 13)
		{
			MessageBox(0, L"请输入正确的13位ISBN码。", L"错误", MB_ICONERROR);
			return 0;
		}
		BookInfo* bi = (BookInfo*)sv_db_info->Selection(sv_db_info->Selected(), 0)->val;
		bi->name = te_dvs[0]->Content();
		bi->author = te_dvs[1]->Content();
		bi->publisher = te_dvs[2]->Content();
		for (int i = 13; i-- > 0;)
		{
			auto isbn = te_dvs[3]->Content();
			bi->ISBN[i] = (char)isbn[i];
		}
		bi->catagory = te_dvs[4]->Content();
		bi->price = stof(te_dvs[5]->Content()) * 100;
		bi->lentLimitation = stof(te_dvs[6]->Content()) * 24 * 60 * 60;
		bi->priceOverduePd = stof(te_dvs[7]->Content()) * 100;

		e_db->Content(to_wstring(bi->identifier()));
		cb_db_s_clk(0, 0, 0, 0);
		sv_db_info->Selected(0);
		cb_sv_s(0, 0, 0, 0);
	}
	return 0;
}
LRESULT cb_db_newb_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	RunInUIThread([]()
		{
			BookInfo bk("0000000000000", L"默认分类", L"新建书籍", L"新建书籍", L"新建书籍", 0);
			e_db->Content(to_wstring(libm.AMBookInfo(bk)));
			cb_db_s_clk(0, 0, 0, 0);
			sv_db_info->Selected(0);
			cb_sv_s(0, 0, 0, 0);

		});
	return 0;
}
LRESULT cb_db_rmi_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (sv_db->Selected() >= 0)
	{
		Book* bk = (Book*)sv_db->Selection(sv_db->Selected(), 0)->val;
		if (libm.RMBookInstance(bk->identifier()))
			MessageBox(0, L"删除成功", L"成功", MB_ICONWARNING);
		else MessageBox(0, L"删除失败", L"失败", MB_ICONERROR);
		cb_db_s_clk(0, 0, 0, 0);
	}
	return 0;
}

LRESULT cb_br_sv_s(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	Borrower* br = (Borrower*)bor.sv_br->Selection(wparam, 0)->val;
	bor.l_id->Content(to_wstring(br->identifier()));
	bor.te_dvs[0]->Content(br->publicIdentifier);
	bor.te_dvs[1]->Content(br->name);
	bor.te_dvs[2]->Content((bool)br->sex ? L"男" : L"女");
	bor.te_dvs[3]->Content(timefmt(br->born, false));
	bor.te_dvs[4]->Content(to_wstring(br->balance / 100.0f));
	bor.sv_detl->Clear();
	for (auto i = br->lents.rbegin(); i != br->lents.rend(); i++)
	{
		bor.sv_detl->AddRow({
			{i->book->info()->name,0},
			{timefmt(i->lent->lentout,false),0},
			{i->lent->returntime ? timefmt(i->lent->returntime,false) : L"待还" ,0}
			});
	}
	return 0;
}
LRESULT cb_br_s_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	int fts = 0;
	for (int i = 0; i < 6; i++)
		if (ckb_filters_db[i]->Checked())
			fts = fts | ckb_filters_db[i]->value;
	wstring keyw(bor.e_db->Content());
	auto c = libm.SelectBorrower(keyw, (RFILTER)fts);
	RunInUIThread([c]() {
		bor.sv_br->Clear();
		for (auto i = c.begin(); i != c.end(); i++)
		{
			bor.sv_br->AddRow({
				{to_wstring((*i)->identifier()),(*i)},
				{(*i)->publicIdentifier,0},
				{(*i)->name},
				{(bool)(*i)->sex ? L"男" : L"女"},
				{timefmt((*i)->born,false),0},
				{to_wstring((*i)->balance / 100.0f),0}
				});
		}

		});
	return 0;
}
LRESULT cb_br_tg_edr(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	bor.sv_detl->disabled = true;
	bor.srv_editor->disabled = true;
	if (bor.tg_edit->Checked())
	{
		Animate(&cb_pc_anim, 800, (WPARAM)bor.srv_editor, (LPARAM)bor.sv_detl);
	}
	else
	{
		Animate(&cb_pc_anim, 800, (WPARAM)bor.sv_detl, (LPARAM)bor.srv_editor);
	}
	return 0;
}
LRESULT cb_br_newb_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	Borrower br(L"借阅人", 1, L"000000000", SEX_FEMALE);
	bor.e_db->Content(to_wstring(libm.AMBorrower(br)));
	cb_br_s_clk(0, 0, 0, 0);
	bor.sv_br->Selected(0);
	cb_br_sv_s(0, 0, 0, 0);
	return 0;
}
LRESULT cb_br_modify_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (bor.sv_br->Selected() >= 0)
	{
		Borrower* br = (Borrower*)bor.sv_br->Selection(bor.sv_br->Selected(), 0)->val;
		br->publicIdentifier = bor.te_dvs[0]->Content();
		br->name = bor.te_dvs[1]->Content();
		if (bor.te_dvs[2]->Content() == L"男")
			br->sex = SEX_MALE;
		else if (bor.te_dvs[2]->Content() == L"女")
			br->sex = SEX_FEMALE;
		else { MessageBox(0, L"性别无效", L"错误", MB_ICONERROR); return 0; }

		wstring fmtt = bor.te_dvs[3]->Content();
		vector<wstring> token;
		split(fmtt, token, L"-");
		if (token.size() != 3) { MessageBox(0, L"生日无效", L"错误", MB_ICONERROR); return 0; }
		tm bt;
		bt.tm_year = stoi(token[0]) - 1900;
		bt.tm_mon = stoi(token[1]) - 1;
		bt.tm_mday = stoi(token[2]);
		bt.tm_hour = 0;
		bt.tm_min = 0;
		bt.tm_sec = 1;
		bt.tm_isdst = -1;
		br->born = mktime(&bt);
		br->balance = stof(bor.te_dvs[4]->Content()) * 100;
		bor.e_db->Content(to_wstring(br->identifier()));
		cb_br_s_clk(0, 0, 0, 0);
		bor.sv_br->Selected(0);
		cb_br_sv_s(0, 0, 0, 0);
	}

	return 0;
}

LRESULT cb_bl_lent(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (bl.te_bkid->Content().length() == 0) return 0;
	if (bl.te_brpid->Content().length() == 0) return 0;
	Book* bk = libm.GetBook(stoll(bl.te_bkid->Content()));
	Borrower* br = nullptr;
	auto brs = libm.SelectBorrower(bl.te_brpid->Content(), RFILTER_PUBLICID);
	{
		if (brs.size() > 0) br = brs[0];
		if (bk)
		{
			bl.l_bkinf->Content(L"书本信息:\n名称:" + bk->info()->name + L"\n出版社:" + bk->info()->publisher);
		}
		else
		{
			bl.l_bkinf->Content(L"书本信息:\n未找到");
		}
		if (br)
		{
			bl.l_brinf->Content(L"借阅人信息:\n姓名:" + br->name);
		}
		else
		{
			bl.l_brinf->Content(L"借阅人信息:\n未找到");
		}}
	if (!bk || !br) return 0;
	auto ret = libm.NewLent(bk->identifier(), { br->identifier(),time(0),bk->info()->lentLimitation,0 });
	if (ret == LNTERR_OK) MessageBox(0, L"借书成功", L"成功", MB_ICONWARNING);
	else MessageBox(0, L"借书失败", L"失败", MB_ICONERROR);
	return 0;
}
LRESULT cb_bl_ret(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (bl.te_bkid->Content().length() == 0) return 0;
	if (bl.te_brpid->Content().length() == 0) return 0;
	Book* bk = libm.GetBook(stoll(bl.te_bkid->Content()));
	Borrower* br = nullptr;
	auto brs = libm.SelectBorrower(bl.te_brpid->Content(), RFILTER_PUBLICID);
	{
		if (brs.size() > 0) br = brs[0];
		if (bk)
		{
			bl.l_bkinf->Content(L"书本信息:\n名称:" + bk->info()->name + L"\n出版社:" + bk->info()->publisher);
		}
		else
		{
			bl.l_bkinf->Content(L"书本信息:\n未找到");
		}
		if (br)
		{
			bl.l_brinf->Content(L"借阅人信息:\n姓名:" + br->name);
		}
		else
		{
			bl.l_brinf->Content(L"借阅人信息:\n未找到");
		}}
	if (!bk || !br) return 0;
	auto ret = libm.ReturnLent(bk->identifier(), br->identifier());
	if (ret == RETERR_OK) MessageBox(0, L"还书成功", L"成功", MB_ICONWARNING);
	else if (ret == RETERR_NOBALANCE) MessageBox(0, L"还书失败 余额不足", L"失败", MB_ICONERROR);
	else MessageBox(0, L"还书失败", L"失败", MB_ICONERROR);
	return 0;
}
LRESULT cb_bl_qr(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	if (bl.te_bkid->Content().length() == 0) return 0;
	if (bl.te_brpid->Content().length() == 0) return 0;
	Book* bk = libm.GetBook(stoll(bl.te_bkid->Content()));
	Borrower* br = nullptr;
	auto brs = libm.SelectBorrower(bl.te_brpid->Content(), RFILTER_PUBLICID);
	{
		if (brs.size() > 0) br = brs[0];
		if (bk)
		{
			bl.l_bkinf->Content(L"书本信息:\n名称:" + bk->info()->name + L"\n出版社:" + bk->info()->publisher);
		}
		else
		{
			bl.l_bkinf->Content(L"书本信息:\n未找到");
		}
		if (br)
		{
			bl.l_brinf->Content(L"借阅人信息:\n姓名:" + br->name);
		}
		else
		{
			bl.l_brinf->Content(L"借阅人信息:\n未找到");
		}}
	if (br && bk)
		bl.l_bill->Content(L"账单:\n余额:" + to_wstring(br->balance * 0.01f) + L"\n待支付:" + to_wstring(libm.GetBill(bk->identifier(), br->identifier()) * 0.01f));
	return 0;
}

LRESULT cb_rec_s_clk(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	rec.sv_br->Clear();
	auto res = libm.SelectRecord(rec.e_db->Content());
	RunInUIThread([res]() {
		for (auto i = res.begin(); i != res.end(); i++)
		{
			Borrower* br = libm.GetBorrower(i->lent.borrower);
			Book* bk = i->book;
			if (!br || !bk) continue;
			rec.sv_br->AddRow({
				{br->name,0},
				{br->publicIdentifier,0},
				{bk->info()->name,0},
				{bk->info()->GetISBN(),0},
				{timefmt(i->lent.lentout,false),0},
				{timefmt(i->lent.lentout + i->lent.limitation,false),0},
				{i->lent.returntime ? timefmt(i->lent.returntime,false) : L"待归还",0}
				});
		}

		});
	return 0;
}

LRESULT cb_close(View* view, Message msg, WPARAM wparam, LPARAM lparam)
{
	PostQuitMessage(0);
	return 0;
}
Panel* tpnl;

HRSRC rgif;
HRSRC rpng;

HGLOBAL ggif;
HGLOBAL gpng;

HWND thwnd; Frame* tFrame;
int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	rgif = FindResource(0, MAKEINTRESOURCE(IDR_GIF2), L"GIF");
	ggif = LoadResource(0, rgif);

	rpng = FindResource(0, MAKEINTRESOURCE(IDB_PNG1), L"PNG");
	gpng = LoadResource(0, rpng);

	Initiate();
	//Test();
	//return 0;
	Frame mainFrame({ 1280,720 });
	//mainFrame.AddEventListener(0, &cb_close, FE_DESTROY);
	mainFrame.Title(L"图书管理系统");
	tFrame = &mainFrame;
	thwnd = mainFrame.GetNative();

	SectionBar sb(&mainFrame);
	sb.AddEventListener(nullptr, &cb_sb_sc, SBE_OPTIONCHANGED);
	sb.Position({ 10, 30 });
	Panel pn_bn(&mainFrame);
	{
		pn_bn.Position({ 10,75 });
		pn_bn.Size({ 10,10 });
		pn_bn.Coord(COORD_FILL, COORD_FILL);
		pn_bn.Anchor({ 0.5f,0.5f });
	}
	InitInstance(&pn_bn);

	Panel pn_br(&mainFrame);
	{
		pn_br.Position({ 10,75 });
		pn_br.Size({ 10,10 });
		pn_br.Coord(COORD_FILL, COORD_FILL);
		pn_br.disabled = true;
		pn_br.Anchor({ 0.5f,0.5f });
		pn_br.Alpha(1);
	}
	InitBorrower(&pn_br);

	Panel pn_lr(&mainFrame);
	{
		pn_lr.Position({ 10,75 });
		pn_lr.Size({ 10,10 });
		pn_lr.Coord(COORD_FILL, COORD_FILL);
		pn_lr.disabled = true;
		pn_lr.Anchor({ 0.5f,0.5f });
		pn_lr.Alpha(1);
	}
	InitLentret(&pn_lr);
	tpnl = &pn_lr;

	Panel pn_rc(&mainFrame);
	{
		pn_rc.Position({ 10,75 });
		pn_rc.Size({ 10,10 });
		pn_rc.Coord(COORD_FILL, COORD_FILL);
		pn_rc.disabled = true;
		pn_rc.Anchor({ 0.5f,0.5f });
		pn_rc.Alpha(1);
	}
	InitRecord(&pn_rc);

	sb.AddOption(L"书", &pn_bn);
	sb.AddOption(L"借阅人", &pn_br);
	sb.AddOption(L"记录", &pn_rc);
	sb.AddOption(L"借还", &pn_lr);

	mainFrame.Show();
	mainFrame.MainLoop();
	//libm.Commit();
	return 0;
}

Menu* tMenu = nullptr;
RadioButton* trb;
void cbtest(View* v, Message m, WPARAM w, LPARAM l)
{
	//EnterCriticalSection(&gThreadAccess);
	//auto hm = CreatePopupMenu();
	//for (int i = 0; i < 1; i++)
	//{
	//	AppendMenuW(hm, MF_OWNERDRAW, 0, L"MenuItem 0");
	//	AppendMenuW(hm, MF_OWNERDRAW, 0, L"MenuItem 1");
	//	AppendMenuW(hm, 0, 0, L"MenuItem 2");
	//	AppendMenuW(hm, 0, 0, L"MenuItem 3");
	//}
	//if (!tMenu)
	//{
	//	tMenu = new Menu(L"File");
	//	tMenu->AppendItem(MenuItem::Common(0, 0, L"New", L"Ctrl+N"));
	//	tMenu->AppendItem(MenuItem::Common(0, 0, L"Open", L""));

	//	Menu* sub = new Menu(L"Recent");
	//	sub->AppendItem(MenuItem::Common(0, 0, L"FlameUI.sln", L""));
	//	sub->AppendItem(MenuItem::Common(0, 0, L"GxEngine.sln", L""));
	//	sub->AppendItem(MenuItem::Seperator());
	//	sub->AppendItem(MenuItem::Common(0, 0, L"C:\\Windows\\System\\", L""));
	//	sub->AppendItem(MenuItem::Common(0, 0, L"D:\\Documents\\Vieoes\\", L""));
	//	sub->AppendItem(MenuItem::Seperator());
	//	sub->AppendItem(MenuItem::SubMenu(0, sub));

	//	tMenu->AppendItem(MenuItem::Seperator());
	//	tMenu->AppendItem(MenuItem::Common(0, 0, L"Save", L"Ctrl+S",true));
	//	tMenu->AppendItem(MenuItem::Common(0, 0, L"Save as", L"", true));

	//	tMenu->AppendItem(MenuItem::SubMenu(0,sub));
	//	tMenu->AppendItem(MenuItem::Seperator());
	//	tMenu->AppendItem(MenuItem::Common(0, 0, L"Exit", L""));
	//}
	//PopupMenu(tFrame, tMenu, nullptr);
	//POINT cp;
	//GetCursorPos(&cp);
	////int hr = TrackPopupMenu(hm, TPM_RETURNCMD, cp.x, cp.y, 0, thwnd, nullptr);
	////std::cout << hr;
	////return;
	Frame* secFrame = new Frame({ 800,600 }, { 0,0 });
	//secFrame->close = false;
	//secFrame->minimal = false;
	//secFrame->maximal = false;
	secFrame->titled = false;
	secFrame->Title(L"Docker");
	secFrame->Show();
	auto dp = new DockProvider(secFrame);
	RunInUIThread([secFrame, dp]() {
		auto pp = dp->AddTab(L"Animated GIF");
		Label* ttl = new Label(pp, L"Well-known animation format.");
		ttl->Position({ 10,10 });
		//auto shl = new SeperatorHandle(pp);
		//shl->Position({ 50,0 });
		//auto shr = new SeperatorHandle(pp);
		//shr->Position({ 80,0 });
		//auto sht = new SeperatorHandle(pp, true);
		//sht->Position({ 0,50 });
		//auto shb = new SeperatorHandle(pp, true);
		//shb->Position({ 0,80 });

		Button* btn = new Button(pp);
		btn->Position({ 10,40 });
		//btn->Size({ 80,32 });
		Label* t = new Label(btn, L"Confirm");
		t->Coord(COORD_CENTER, COORD_CENTER);
		//shl->BindEdge(EDGE_LEFT, btn);
		//sht->BindEdge(EDGE_TOP, btn);
		//shr->BindEdge(EDGE_RIGHT, btn);
		//shb->BindEdge(EDGE_BOTTOM, btn);

		Image* img = new Image(pp);
		img->Content(ggif, SizeofResource(0, rgif));
		//img->Content(L"I:\\Pictures\\azis.gif");
		//RunInMainThread([img]() {img->Content(L"I:\\Pictures\\azis2.gif");  });
		//RunInMainThread([img]() {img->Content(L"I:\\Pictures\\11.bmp.gif");  });

		img->Position({ 10,100 });

		pp = dp->AddTab(L"Static Image");
		ttl = new Label(pp, L"Common non-animated image.");
		ttl->Position({ 10,0 });

		img = new Image(pp);
		//img->Content(L"I:\\Pictures\\3.bmp");
		img->Content(gpng, SizeofResource(0, rpng));
		//img->Content(L"N:\\Video\\Apex Legends\\Apex Legends 2021.08.22 - 01.51.31.02.DVR.mp4");
		//RunInMainThread([img]() {img->Content(L"I:\\Pictures\\azis2.gif");  });
		//RunInMainThread([img]() {img->Content(L"I:\\Pictures\\11.bmp.gif");  });

		img->Position({ 10,40 });

		pp = dp->AddTab(L"ImGui");
		ttl = new Label(pp, L"ImGuiCanvas --------\nImGui");
		ttl->Position({ 10,0 });
		ImGuiCanvas* ic = new ImGuiCanvas(pp);
		ic->Position({ 10,40 });
		ic->Size({ 10,10 });
		ic->Coord(COORD_FILL, COORD_FILL);
		trb->Parent(tpnl);
		});
	//secFrame->AddEventListener(0, &cb_close, FE_DESTROY);
	//secFrame->MainLoop(true);
	//LeaveCriticalSection(&gThreadAccess);
}
void InitInstance(View* pnl)
{
	e_db = new TextEditor(pnl);
	e_db->Size({ 300,32 });
	e_db->Position({ 15,0 });
	Button* btn_db_sr = new Button(pnl);
	btn_db_sr->Position({ 325,0 });
	btn_db_sr->Size({ 80,32 });
	btn_db_sr->AddEventListener(nullptr, &cb_db_s_clk, FE_LBUTTONUP);
	Label* t = new Label(btn_db_sr, L"搜索");
	t->Coord(COORD_CENTER, COORD_CENTER);

	tg_fold = new Toggle(pnl);
	tg_fold->SizeMode(SIZE_MODE_CHILDREN, SIZE_MODE_NONE);
	tg_fold->Position({ 420,0 });
	tg_fold->AddEventListener(nullptr, &cb_tg_fd_vc, FE_CHANGE);
	t = new Label(tg_fold, L"折叠");
	t->Coord(COORD_CENTER, COORD_CENTER);

	auto rdbt = new RadioButton(pnl);
	rdbt->SizeMode(SIZE_MODE_CHILDREN, SIZE_MODE_CHILDREN);
	rdbt->Position({ 450,0 });
	rdbt->AddEventListener(nullptr, &cbtest, FE_RBUTTONDOWN);
	//PostEvent(rdbt, FE_RBUTTONDOWN, 0, 0);
	trb = rdbt;
	t = new Label(rdbt, L"RadioBox");
	t->Coord(COORD_CENTER, COORD_CENTER);
	rdbt->ZOrder(-1);
	{
		Panel* p = new Panel(pnl);
		pnl_infedr = p;
		p->Anchor({ 0.5,0.5 });
		p->Coord(COORD_NEGATIVE, COORD_FILL);
		p->Position({ 15, 75 });
		p->Size({ 320, 25 });
		sv_detl = new SheetView(p);
		sv_detl->Coord(COORD_FILL, COORD_FILL);
		sv_detl->Position({ 0, 0 });
		sv_detl->Size({ 0, 40 });
		sv_detl->AddTitle(L"借出人")->AddTitle(L"借出时间")->AddTitle(L"归还时间");
		btn_db_sr = new Button(p);
		btn_db_sr->Coord(COORD_FILL, COORD_NEGATIVE);
		btn_db_sr->Position({ 0, 0 });
		btn_db_sr->Size({ 0, 32 });
		btn_db_sr->AddEventListener(nullptr, &cb_db_rmi_clk, FE_LBUTTONUP);
		Label* t = new Label(btn_db_sr, L"删除");
		t->Coord(COORD_CENTER, COORD_CENTER);


		srv_det = new ScrollView(pnl);
		srv_det->Coord(COORD_NEGATIVE, COORD_FILL);
		srv_det->Position({ 15, 75 });
		srv_det->Size({ 320, 25 });
		srv_det->Anchor({ 0.5,0.5 });
		srv_det->Content()->Layouter(new LinearPlacer(DIRECTION_VERTICAL, 5));
		srv_det->disabled = true;
		srv_det->Alpha(1);


		t = new Label(srv_det->Content(), L"编号:");
		l_dv_id = new Label(srv_det->Content(), L"0000");
		t = new Label(srv_det->Content(), L"名称:");
		te_dvs[0] = new TextEditor(srv_det->Content());
		te_dvs[0]->Size({ 240,32 });
		t = new Label(srv_det->Content(), L"作者:");
		te_dvs[1] = new TextEditor(srv_det->Content());
		te_dvs[1]->Size({ 240,32 });
		t = new Label(srv_det->Content(), L"出版社:");
		te_dvs[2] = new TextEditor(srv_det->Content());
		te_dvs[2]->Size({ 240,32 });
		t = new Label(srv_det->Content(), L"ISBN:");
		te_dvs[3] = new TextEditor(srv_det->Content());
		te_dvs[3]->Size({ 240,32 });
		t = new Label(srv_det->Content(), L"分类:");
		te_dvs[4] = new TextEditor(srv_det->Content());
		te_dvs[4]->Size({ 240,32 });
		t = new Label(srv_det->Content(), L"价格:");
		te_dvs[5] = new TextEditor(srv_det->Content());
		te_dvs[5]->Size({ 240,32 });

		t = new Label(srv_det->Content(), L"归还期限(天):");
		te_dvs[6] = new TextEditor(srv_det->Content());
		te_dvs[6]->Size({ 240,32 });

		t = new Label(srv_det->Content(), L"罚款(元/每天):");
		te_dvs[7] = new TextEditor(srv_det->Content());
		te_dvs[7]->Size({ 240,32 });


		btn_db_sr = new Button(srv_det->Content());
		btn_db_sr->Coord(COORD_CENTER, COORD_POSTIVE);
		btn_db_sr->Size({ 80,32 });
		btn_db_sr->AddEventListener(nullptr, &cb_db_modify_clk, FE_LBUTTONUP);
		t = new Label(btn_db_sr, L"修改");
		t->Coord(COORD_CENTER, COORD_CENTER);

		btn_db_sr = new Button(srv_det->Content());
		btn_db_sr->Coord(COORD_CENTER, COORD_POSTIVE);
		btn_db_sr->Size({ 80,32 });
		btn_db_sr->AddEventListener(nullptr, &cb_db_newb_clk, FE_LBUTTONUP);
		t = new Label(btn_db_sr, L"新建书籍");
		t->Coord(COORD_CENTER, COORD_CENTER);

		t = new Label(srv_det->Content(), L"待添加数量:");
		te_dvs[8] = new TextEditor(srv_det->Content());
		te_dvs[8]->Size({ 240,32 });
		te_dvs[8]->Content(L"1");
		btn_db_sr = new Button(srv_det->Content());
		btn_db_sr->Coord(COORD_CENTER, COORD_POSTIVE);
		btn_db_sr->Size({ 80,32 });
		btn_db_sr->AddEventListener(nullptr, &cb_db_addi_clk, FE_LBUTTONUP);
		t = new Label(btn_db_sr, L"添加库存");
		t->Coord(COORD_CENTER, COORD_CENTER);

	}

	sv_db = new SheetView(pnl);
	sv_db->Size({ 350, 25 });
	sv_db->Position({ 15, 75 });
	sv_db->Coord(COORD_FILL, COORD_FILL);
	sv_db->Anchor({ 0.5,0.5 });
	sv_db->AddEventListener(nullptr, &cb_sv_s, SVE_SELECT);

	sv_db_info = new SheetView(pnl);
	sv_db_info->Size({ 350, 25 });
	sv_db_info->Position({ 15, 75 });
	sv_db_info->Coord(COORD_FILL, COORD_FILL);
	sv_db_info->Alpha(1);
	sv_db_info->disabled = true;
	sv_db_info->Anchor({ 0.5,0.5 });
	sv_db_info->AddEventListener(nullptr, &cb_sv_s, SVE_SELECT);

	wstring cols[6]{ L"编号",L"名称",L"作者",L"出版社",L"ISBN",L"分类" };
	for (int i = 0; i < 6; i++)
	{
		ckb_filters_db[i] = new CheckBox(pnl);
		ckb_filters_db[i]->Position({ 15.0f + 80.0f * i,40.0f });
		ckb_filters_db[i]->SizeMode(SIZE_MODE_CHILDREN, SIZE_MODE_NONE);
		ckb_filters_db[i]->Checked(true);
		ckb_filters_db[i]->value = (long long)(1 << i);
		t = new Label(ckb_filters_db[i], cols[i]);
		t->Coord(COORD_POSTIVE, COORD_CENTER);
		if (i == 5)
		{
			sv_db->AddTitle(cols[i], 0.5f);
			sv_db_info->AddTitle(cols[i]);
		}
		else
		{
			sv_db->AddTitle(cols[i]);
			sv_db_info->AddTitle(cols[i]);
		}

	}
	sv_db->AddTitle(L"状态");
	sv_db_info->AddTitle(L"数量");

}
void InitLentret(View* pnl)
{
	Label* t = new Label(pnl, L"借阅人学号:");
	bl.te_brpid = new TextEditor(pnl);
	bl.te_brpid->Position({ 0,30 });
	bl.te_brpid->Size({ 240,32 });
	bl.l_brinf = new Label(pnl, L"借阅人信息:");
	bl.l_brinf->Position({ 0,70 });
	Button* btn = new Button(pnl);
	btn->Position({ 900,0 });
	btn->Size({ 90, 32 });
	btn->AddEventListener(nullptr, &cb_bl_qr, FE_LBUTTONUP);
	t = new Label(btn, L"查询");
	t->Coord(COORD_CENTER, COORD_CENTER);

	btn = new Button(pnl);
	btn->Position({ 900,40 });
	btn->Size({ 90, 32 });
	btn->AddEventListener(nullptr, &cb_bl_lent, FE_LBUTTONUP);
	t = new Label(btn, L"借书");
	t->Coord(COORD_CENTER, COORD_CENTER);

	t = new Label(pnl, L"书本编号:");
	t->Position({ 300,0 });
	bl.te_bkid = new TextEditor(pnl);
	bl.te_bkid->Position({ 300,30 });
	bl.te_bkid->Size({ 240,32 });
	bl.l_bkinf = new Label(pnl, L"书本信息:");
	bl.l_bkinf->Position({ 300,70 });

	bl.l_bill = new Label(pnl, L"账单:");
	bl.l_bill->Position({ 600,0 });

	btn = new Button(pnl);
	btn->Position({ 900,80 });
	btn->Size({ 90, 32 });
	btn->AddEventListener(nullptr, &cb_bl_ret, FE_LBUTTONUP);
	t = new Label(btn, L"还书");
	t->Coord(COORD_CENTER, COORD_CENTER);

}
void InitBorrower(View* pnl)
{
	bor.e_db = new TextEditor(pnl);
	bor.e_db->Size({ 300,32 });
	bor.e_db->Position({ 15,0 });
	Button* btn_db_sr = new Button(pnl);
	btn_db_sr->Position({ 325,0 });
	btn_db_sr->Size({ 80,32 });
	btn_db_sr->AddEventListener(nullptr, &cb_br_s_clk, FE_LBUTTONUP);
	Label* t = new Label(btn_db_sr, L"搜索");
	t->Coord(COORD_CENTER, COORD_CENTER);

	bor.tg_edit = new Toggle(pnl);
	bor.tg_edit->SizeMode(SIZE_MODE_CHILDREN, SIZE_MODE_NONE);
	bor.tg_edit->Position({ 420,0 });
	bor.tg_edit->AddEventListener(nullptr, &cb_br_tg_edr, FE_CHANGE);
	t = new Label(bor.tg_edit, L"编辑");
	t->Coord(COORD_CENTER, COORD_CENTER);

	bor.sv_br = new SheetView(pnl);
	bor.sv_br->Coord(COORD_FILL, COORD_FILL);
	bor.sv_br->Size({ 400, 25 });
	bor.sv_br->Position({ 15, 75 });
	bor.sv_br->Anchor({ 0.5,0.5 });
	bor.sv_br->AddEventListener(nullptr, &cb_br_sv_s, SVE_SELECT);

	{
		bor.sv_detl = new SheetView(pnl);
		bor.sv_detl->Anchor({ 0.5,0.5 });
		bor.sv_detl->Coord(COORD_NEGATIVE, COORD_FILL);
		bor.sv_detl->Position({ 15,75 });
		bor.sv_detl->Size({ 375,25 });
		bor.sv_detl->AddTitle(L"书名")->AddTitle(L"借书时间")->AddTitle(L"还书时间");

		bor.srv_editor = new ScrollView(pnl);
		bor.srv_editor->Anchor({ 0.5,0.5 });
		bor.srv_editor->Coord(COORD_NEGATIVE, COORD_FILL);
		bor.srv_editor->Position({ 15,75 });
		bor.srv_editor->Size({ 375,25 });
		bor.srv_editor->Alpha(1);
		bor.srv_editor->disabled = true;
		bor.srv_editor->Content()->Layouter(new LinearPlacer(DIRECTION_VERTICAL, 10));
		View* prn = bor.srv_editor->Content();

		t = new Label(prn, L"编号");
		bor.l_id = new Label(prn, L"0000");
		t = new Label(prn, L"学号");
		bor.te_dvs[0] = new TextEditor(prn);
		bor.te_dvs[0]->Size({ 240,32 });
		t = new Label(prn, L"姓名");
		bor.te_dvs[1] = new TextEditor(prn);
		bor.te_dvs[1]->Size({ 240,32 });
		t = new Label(prn, L"性别");
		bor.te_dvs[2] = new TextEditor(prn);
		bor.te_dvs[2]->Size({ 240,32 });
		t = new Label(prn, L"生日");
		bor.te_dvs[3] = new TextEditor(prn);
		bor.te_dvs[3]->Size({ 240,32 });
		t = new Label(prn, L"余额");
		bor.te_dvs[4] = new TextEditor(prn);
		bor.te_dvs[4]->Size({ 240,32 });

		btn_db_sr = new Button(prn);
		btn_db_sr->Position({ 0,0 });
		btn_db_sr->Size({ 240,32 });
		btn_db_sr->AddEventListener(nullptr, &cb_br_newb_clk, FE_LBUTTONUP);
		t = new Label(btn_db_sr, L"新建借书人");
		t->Coord(COORD_CENTER, COORD_CENTER);

		btn_db_sr = new Button(prn);
		btn_db_sr->Position({ 0,0 });
		btn_db_sr->Size({ 240,32 });
		btn_db_sr->AddEventListener(nullptr, &cb_br_modify_clk, FE_LBUTTONUP);
		t = new Label(btn_db_sr, L"修改");
		t->Coord(COORD_CENTER, COORD_CENTER);

	}

	wstring cols[]{ L"编号",L"学号",L"姓名",L"性别",L"生日" };
	for (int i = 0; i < 5; i++)
	{
		bor.ckb_filters_db[i] = new CheckBox(pnl);
		bor.ckb_filters_db[i]->Position({ 15.0f + 80.0f * i,40.0f });
		bor.ckb_filters_db[i]->SizeMode(SIZE_MODE_CHILDREN, SIZE_MODE_NONE);
		bor.ckb_filters_db[i]->Checked(true);
		bor.ckb_filters_db[i]->value = (long long)(1 << i);
		t = new Label(bor.ckb_filters_db[i], cols[i]);
		t->Coord(COORD_POSTIVE, COORD_CENTER);
		if (i == 3)
			bor.sv_br->AddTitle(cols[i], 0.4f);
		else
			bor.sv_br->AddTitle(cols[i]);

	}
	bor.sv_br->AddTitle(L"余额", 0.5f);


}
void InitRecord(View* pnl)
{
	rec.e_db = new TextEditor(pnl);
	rec.e_db->Size({ 300,32 });
	rec.e_db->Position({ 15,0 });
	Button* btn_db_sr = new Button(pnl);
	btn_db_sr->Position({ 325,0 });
	btn_db_sr->Size({ 80,32 });
	btn_db_sr->AddEventListener(nullptr, &cb_rec_s_clk, FE_LBUTTONUP);
	Label* t = new Label(btn_db_sr, L"搜索");
	t->Coord(COORD_CENTER, COORD_CENTER);


	rec.sv_br = new SheetView(pnl);
	rec.sv_br->Coord(COORD_FILL, COORD_FILL);
	rec.sv_br->Size({ 25, 25 });
	rec.sv_br->Position({ 15, 45 });
	rec.sv_br->Anchor({ 0.5,0.5 });
	//rec.sv_br->AddEventListener(nullptr, &cb_br_sv_s, SVE_SELECT);

	rec.sv_br->AddTitle(L"借阅人")->AddTitle(L"学号")->AddTitle(L"书名")->AddTitle(L"ISBN")->AddTitle(L"借出时间")->AddTitle(L"期限时间")->AddTitle(L"归还时间");


}