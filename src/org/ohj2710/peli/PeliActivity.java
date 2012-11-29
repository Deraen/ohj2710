package org.ohj2710.peli;

import org.libsdl.app.SDLActivity;

// import android.os.*;
import android.view.*;

/*
 * A sample wrapper class that just calls SDLActivity
 */

public class PeliActivity extends SDLActivity {
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        switch (event.getKeyCode()) {
        // forward volume keys to Android
        case KeyEvent.KEYCODE_VOLUME_UP:
        case KeyEvent.KEYCODE_VOLUME_DOWN:
            return false;
        }
        return super.dispatchKeyEvent(event);
    }

    // @Override
    // protected void onCreate(Bundle savedInstanceState) {
    //     super.onCreate(savedInstanceState);

    //     // fullscreen
    //     requestWindowFeature(Window.FEATURE_NO_TITLE);
    //     getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
    // }
}
