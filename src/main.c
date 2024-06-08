#include "Windows.h"
#include "stdio.h"
#include "string.h"

#define SB_IMPLEMENTATION
#include "sb.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    if (!OpenClipboard(NULL))
    {
        return EXIT_FAILURE;
    }

    HANDLE clipboard_data = GetClipboardData(CF_TEXT);

    if (clipboard_data == NULL)
    {
        if (clipboard_data)
            GlobalUnlock(clipboard_data);
        if (clipboard_data)
            CloseClipboard();

        return EXIT_FAILURE;
    }

    String_Builder *builder = sb_create(strlen(clipboard_data));

    if (builder == NULL)
    {
        if (clipboard_data)
            GlobalUnlock(clipboard_data);
        if (clipboard_data)
            CloseClipboard();
        if (builder)
            sb_destroy(builder);

        return EXIT_FAILURE;
    }

    char *clipboard_text = GlobalLock(clipboard_data);

    if (clipboard_text == NULL)
    {
        if (clipboard_data)
            GlobalUnlock(clipboard_data);
        if (clipboard_data)
            CloseClipboard();
        if (builder)
            sb_destroy(builder);

        return EXIT_FAILURE;
    }

    sb_append(builder, clipboard_text);

    if (strstr(builder->data, "https://x.com/") == NULL)
    {
        if (clipboard_data)
            GlobalUnlock(clipboard_data);
        if (clipboard_data)
            CloseClipboard();
        if (builder)
            sb_destroy(builder);

        return EXIT_FAILURE;
    }

    sb_insert(builder, 8, "v");
    sb_insert(builder, 10, "twitter");

    clipboard_text = GlobalReAlloc(clipboard_text, builder->length + 1, GHND);
    strncpy(clipboard_text, builder->data, builder->length);
    GlobalUnlock(clipboard_text);

    EmptyClipboard();
    if (SetClipboardData(CF_TEXT, clipboard_text) == NULL)
    {
        if (clipboard_data)
            GlobalUnlock(clipboard_data);
        if (clipboard_data)
            CloseClipboard();
        if (builder)
            sb_destroy(builder);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}