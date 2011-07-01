#ifndef _PH_TREENEW_H
#define _PH_TREENEW_H

#define PH_TREENEW_CLASSNAME L"PhTreeNew"

typedef struct _PH_TREENEW_COLUMN
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG Visible : 1;
            ULONG CustomDraw : 1;
            ULONG Fixed : 1; // whether this is the fixed column
            ULONG SpareFlags : 29;
        };
    };
    ULONG Id;
    PVOID Context;
    PWSTR Text;
    LONG Width;
    ULONG Alignment;
    ULONG DisplayIndex; // -1 for fixed column or invalid

    ULONG TextFlags;

    struct
    {
        LONG ViewIndex; // actual index in header control
        LONG ViewX; // 0 for the fixed column, and an offset from the divider for normal columns
    } s;
} PH_TREENEW_COLUMN, *PPH_TREENEW_COLUMN;

typedef struct _PH_TREENEW_NODE
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG Visible : 1;
            ULONG Selected : 1;
            ULONG Expanded : 1;
            ULONG UseAutoForeColor : 1;
            ULONG UseTempBackColor : 1;
            ULONG SpareFlags : 27;
        };
    };

    COLORREF BackColor;
    COLORREF ForeColor;
    COLORREF TempBackColor;
    HFONT Font;
    HICON Icon;

    PPH_STRINGREF TextCache;
    ULONG TextCacheSize;

    ULONG Index; // index within the flat list
    ULONG Level; // 0 for root, 1, 2, ...

    struct
    {
        union
        {
            ULONG Flags2;
            struct
            {
                ULONG IsLeaf : 1;
                ULONG CachedColorValid : 1;
                ULONG CachedFontValid : 1;
                ULONG CachedIconValid : 1;
                ULONG SpareFlags2 : 28;
            };
        };

        // Temp. drawing data
        COLORREF DrawBackColor;
        COLORREF DrawForeColor;
    } s;
} PH_TREENEW_NODE, *PPH_TREENEW_NODE;

typedef enum _PH_TREENEW_MESSAGE
{
    TreeNewGetChildren, // PPH_TREENEW_GET_CHILDREN Parameter1
    TreeNewIsLeaf, // PPH_TREENEW_IS_LEAF Parameter1
    TreeNewGetCellText, // PPH_TREENEW_GET_CELL_TEXT Parameter1
    TreeNewGetNodeColor, // PPH_TREENEW_GET_NODE_COLOR Parameter1
    TreeNewGetNodeFont, // PPH_TREENEW_GET_NODE_FONT Parameter1
    TreeNewGetNodeIcon, // PPH_TREENEW_GET_NODE_ICON Parameter1
    TreeNewGetNodeTooltip, // PPH_TREENEW_GET_NODE_TOOLTIP Parameter1
    TreeNewCustomDraw, // PPH_TREENEW_CUSTOM_DRAW Parameter1

    // Notifications
    TreeNewNodeExpanding, // PPH_TREENEW_NODE Parameter1, PPH_TREENEW_NODE_EVENT Parameter2

    TreeNewSortChanged,
    TreeNewSelectionChanged,

    TreeNewKeyDown, // SHORT Parameter1 (Virtual key code)
    TreeNewLeftClick, // PPH_TREENEW_NODE Parameter1, PPH_TREENEW_MOUSE_EVENT Parameter2
    TreeNewRightClick, // PPH_TREENEW_NODE Parameter1, PPH_TREENEW_MOUSE_EVENT Parameter2
    TreeNewLeftDoubleClick, // PPH_TREENEW_NODE Parameter1, PPH_TREENEW_MOUSE_EVENT Parameter2
    TreeNewRightDoubleClick, // PPH_TREENEW_NODE Parameter1, PPH_TREENEW_MOUSE_EVENT Parameter2
    TreeNewContextMenu, // PPH_TREENEW_NODE Parameter1, PPH_TREENEW_MOUSE_EVENT Parameter2

    TreeNewHeaderRightClick,

    MaxTreeNewMessage
} PH_TREENEW_MESSAGE;

typedef BOOLEAN (NTAPI *PPH_TREENEW_CALLBACK)(
    __in HWND hwnd,
    __in PH_TREENEW_MESSAGE Message,
    __in_opt PVOID Parameter1,
    __in_opt PVOID Parameter2,
    __in_opt PVOID Context
    );

// Callback flags
#define TN_CACHE 0x1
#define TN_AUTO_FORECOLOR 0x1000

// Column change flags
#define TN_COLUMN_CONTEXT 0x1
#define TN_COLUMN_TEXT 0x2
#define TN_COLUMN_WIDTH 0x4
#define TN_COLUMN_ALIGNMENT 0x8
#define TN_COLUMN_DISPLAYINDEX 0x10
#define TN_COLUMN_TEXTFLAGS 0x20
#define TN_COLUMN_FLAG_VISIBLE 0x100000
#define TN_COLUMN_FLAG_CUSTOMDRAW 0x200000
#define TN_COLUMN_FLAG_FIXED 0x400000
#define TN_COLUMN_FLAGS 0xfff00000

// Cache flags
#define TN_CACHE_COLOR 0x1
#define TN_CACHE_FONT 0x2
#define TN_CACHE_ICON 0x4

typedef struct _PH_TREENEW_GET_CHILDREN
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;

    ULONG NumberOfChildren;
    PPH_TREENEW_NODE *Children; // can be NULL if no children
} PH_TREENEW_GET_CHILDREN, *PPH_TREENEW_GET_CHILDREN;

typedef struct _PH_TREENEW_IS_LEAF
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;

    BOOLEAN IsLeaf;
} PH_TREENEW_IS_LEAF, *PPH_TREENEW_IS_LEAF;

typedef struct _PH_TREENEW_GET_CELL_TEXT
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;
    ULONG Id;

    PH_STRINGREF Text;
} PH_TREENEW_GET_CELL_TEXT, *PPH_TREENEW_GET_CELL_TEXT;

typedef struct _PH_TREENEW_GET_NODE_COLOR
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;

    COLORREF BackColor;
    COLORREF ForeColor;
} PH_TREENEW_GET_NODE_COLOR, *PPH_TREENEW_GET_NODE_COLOR;

typedef struct _PH_TREENEW_GET_NODE_FONT
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;

    HFONT Font;
} PH_TREENEW_GET_NODE_FONT, *PPH_TREENEW_GET_NODE_FONT;

typedef struct _PH_TREENEW_GET_NODE_ICON
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;

    HICON Icon;
} PH_TREENEW_GET_NODE_ICON, *PPH_TREENEW_GET_NODE_ICON;

typedef struct _PH_TREENEW_GET_NODE_TOOLTIP
{
    ULONG Flags;
    PPH_TREENEW_NODE Node;

    PH_STRINGREF Text;
} PH_TREENEW_GET_NODE_TOOLTIP, *PPH_TREENEW_GET_NODE_TOOLTIP;

typedef struct _PH_TREENEW_CUSTOM_DRAW
{
    PPH_TREENEW_NODE Node;
    PPH_TREENEW_COLUMN Column;

    HDC Dc;
    RECT CellRect;
    RECT TextRect;
} PH_TREENEW_CUSTOM_DRAW, *PPH_TREENEW_CUSTOM_DRAW;

typedef struct _PH_TREENEW_MOUSE_EVENT
{
    ULONG Index;
    ULONG Id;
    POINT Location;
    ULONG KeyFlags;
} PH_TREENEW_MOUSE_EVENT, *PPH_TREENEW_MOUSE_EVENT;

typedef struct _PH_TREENEW_NODE_EVENT
{
    BOOLEAN Handled;
    ULONG Flags;
    PVOID Reserved1;
    PVOID Reserved2;
} PH_TREENEW_NODE_EVENT, *PPH_TREENEW_NODE_EVENT;

#define TNM_FIRST (WM_USER + 1)
#define TNM_SETCALLBACK (WM_USER + 1)
#define TNM_NODESADDED (WM_USER + 2) // unimplemented
#define TNM_NODESREMOVED (WM_USER + 3) // unimplemented
#define TNM_NODESSTRUCTURED (WM_USER + 4)
#define TNM_ADDCOLUMN (WM_USER + 5)
#define TNM_REMOVECOLUMN (WM_USER + 6)
#define TNM_GETCOLUMN (WM_USER + 7)
#define TNM_SETCOLUMN (WM_USER + 8)
#define TNM_GETCOLUMNORDERARRAY (WM_USER + 9)
#define TNM_SETCOLUMNORDERARRAY (WM_USER + 10)
#define TNM_SETCURSOR (WM_USER + 11)
#define TNM_GETSORT (WM_USER + 12)
#define TNM_SETSORT (WM_USER + 13)
#define TNM_SETTRISTATE (WM_USER + 14)
#define TNM_ENSUREVISIBLE (WM_USER + 15)
#define TNM_SCROLL (WM_USER + 16)
#define TNM_GETVISIBLENODECOUNT (WM_USER + 17)
#define TNM_GETVISIBLENODE (WM_USER + 18)
#define TNM_GETNODETEXT (WM_USER + 19)
#define TNM_SETNODESTATE (WM_USER + 20)
#define TNM_SETNODEEXPANDED (WM_USER + 21)
#define TNM_GETMAXID (WM_USER + 22)
#define TNM_SETMAXID (WM_USER + 23)
#define TNM_LAST (WM_USER + 23)

#define TreeNew_SetCallback(hWnd, Callback, Context) \
    SendMessage((hWnd), TNM_SETCALLBACK, (WPARAM)(Context), (LPARAM)(Callback))

#define TreeNew_NodesStructured(hWnd) \
    SendMessage((hWnd), TNM_NODESSTRUCTURED, 0, 0)

#define TreeNew_AddColumn(hWnd, Column) \
    SendMessage((hWnd), TNM_ADDCOLUMN, 0, (LPARAM)(Column))

#define TreeNew_RemoveColumn(hWnd, Id) \
    SendMessage((hWnd), TNM_REMOVECOLUMN, (WPARAM)(Id), 0)

#define TreeNew_GetColumn(hWnd, Id, Column) \
    SendMessage((hWnd), TNM_GETCOLUMN, (WPARAM)(Id), (LPARAM)(Column))

#define TreeNew_SetColumn(hWnd, Mask, Column) \
    SendMessage((hWnd), TNM_SETCOLUMN, (WPARAM)(Mask), (LPARAM)(Column))

#define TreeNew_GetColumnOrderArray(hWnd, Count, Array) \
    SendMessage((hWnd), TNM_GETCOLUMNORDERARRAY, (WPARAM)(Count), (LPARAM)(Array))

#define TreeNew_SetColumnOrderArray(hWnd, Count, Array) \
    SendMessage((hWnd), TNM_SETCOLUMNORDERARRAY, (WPARAM)(Count), (LPARAM)(Array))

#define TreeNew_SetCursor(hWnd, Cursor) \
    SendMessage((hWnd), TNM_SETCURSOR, 0, (LPARAM)(Cursor))

#define TreeNew_GetSort(hWnd, Column, Order) \
    SendMessage((hWnd), TNM_GETSORT, (WPARAM)(Column), (LPARAM)(Order))

#define TreeNew_SetSort(hWnd, Column, Order) \
    SendMessage((hWnd), TNM_SETSORT, (WPARAM)(Column), (LPARAM)(Order))

#define TreeNew_SetTriState(hWnd, TriState) \
    SendMessage((hWnd), TNM_SETTRISTATE, (WPARAM)(TriState), 0)

BOOLEAN PhTreeNewInitialization();

FORCEINLINE VOID PhInitializeTreeNewNode(
    __in PPH_TREENEW_NODE Node
    )
{
    memset(Node, 0, sizeof(PH_TREENEW_NODE));

    Node->Visible = TRUE;
    Node->Expanded = TRUE;
}

FORCEINLINE VOID PhInvalidateTreeNewNode(
    __inout PPH_TREENEW_NODE Node,
    __in ULONG Flags
    )
{
    if (Flags & TN_CACHE_COLOR)
        Node->s.CachedColorValid = FALSE;
    if (Flags & TN_CACHE_FONT)
        Node->s.CachedFontValid = FALSE;
    if (Flags & TN_CACHE_ICON)
        Node->s.CachedIconValid = FALSE;
}

FORCEINLINE BOOLEAN PhAddTreeNewColumn(
    __in HWND hwnd,
    __in ULONG Id,
    __in BOOLEAN Visible,
    __in PWSTR Text,
    __in ULONG Width,
    __in ULONG Alignment,
    __in ULONG DisplayIndex,
    __in ULONG TextFlags
    )
{
    PH_TREENEW_COLUMN column;

    memset(&column, 0, sizeof(PH_TREENEW_COLUMN));
    column.Id = Id;
    column.Visible = Visible;
    column.Text = Text;
    column.Width = Width;
    column.Alignment = Alignment;
    column.DisplayIndex = DisplayIndex;
    column.TextFlags = TextFlags;

    if (DisplayIndex == -2)
        column.Fixed = TRUE;

    return !!TreeNew_AddColumn(hwnd, &column);
}

#endif