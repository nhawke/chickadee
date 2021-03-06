#include "p-lib.hh"

void process_main() {
    sys_kdisplay(KDISPLAY_NONE);

    int r = dprintf(0, "0\n");
    assert_gt(r, 0);

    r = dprintf(1, "1\n");
    assert_gt(r, 0);

    r = dprintf(2, "2\n");
    assert_gt(r, 0);

    r = dprintf(3, "Nope\n");
    assert_eq(r, E_BADF);

    r = dprintf(-1, "Nope\n");
    assert_eq(r, E_BADF);

    r = sys_dup2(2, 3);
    if (r != 0) {
        assert_eq(r, 3);
    }

    r = dprintf(3, "3\n");
    assert_gt(r, 0);

    r = sys_close(3);
    assert_eq(r, 0);

    r = dprintf(3, "Nope\n");
    assert_eq(r, E_BADF);

    r = sys_dup2(2, 3);
    if (r != 0) {
        assert_eq(r, 3);
    }

    r = dprintf(3, "4\n");
    assert_gt(r, 0);

    r = sys_dup2(4, 3);
    assert_eq(r, E_BADF);

    r = dprintf(3, "5\n");
    assert_gt(r, 0);

    r = sys_dup2(3, 3);
    if (r != 0) {
        assert_eq(r, 3);
    }

    r = dprintf(3, "6\n");
    assert_gt(r, 0);

    r = sys_close(0);
    assert_eq(r, 0);

    r = sys_close(1);
    assert_eq(r, 0);

    r = dprintf(0, "Nope\n");
    assert_eq(r, E_BADF);

    r = sys_close(2);
    assert_eq(r, 0);

    r = sys_dup2(3, 2);
    if (r != 0) {
        assert_eq(r, 2);
    }

    r = sys_dup2(2, 0);
    assert_eq(r, 0);

    r = dprintf(2, "7\n");
    assert_gt(r, 0);

    r = dprintf(3, "8\n");
    assert_gt(r, 0);

    r = dprintf(0, "9\n");
    assert_gt(r, 0);


    console_printf("If you see 0-9 in sequence, testvfs succeeded.\n");
    sys_exit(0);
}
