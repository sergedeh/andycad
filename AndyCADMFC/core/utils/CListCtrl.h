#pragma once

class CListCtrl {
public:
    int InsertItem(int nItem, const char* lpszItem) { return 0; }
    int SetItemText(int nItem, int nSubItem, const char* lpszText) { return 0; }
    void DeleteAllItems() {}
};
