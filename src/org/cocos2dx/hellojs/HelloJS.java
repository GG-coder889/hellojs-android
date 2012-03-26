package org.cocos2dx.hellojs;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

public class HelloJS extends Activity {
    static private final String LOGTAG = "HelloJS";

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(LOGTAG, "onCreate");

        setContentView(R.layout.mainmenu);

        LinearLayout linearlayout = (LinearLayout) findViewById(R.id.mainmenu);

        addVersionStringsToLinearLayout(linearlayout);
    }

    static {
        System.loadLibrary("game");
    }

    private void addVersionStringsToLinearLayout(LinearLayout linearlayout) {
        TextView tv = new TextView(this);
        tv.setText(getLibVersions());
        linearlayout.addView(tv);
    }

    private StringBuilder getLibVersions() {
        StringBuilder content = new StringBuilder();
        content.append("Hello Cocos, JS, Android!\n\n");
        content.append("JS VM Version = " + getJSVMVersion() + "\n");
        content.append("Cocos2d Version = " + getCocosVersion() + "\n");
        content.append("Bindings Version = " + getBindingsVersion() + "\n");

        return content;
    }

    private static native String getJSVMVersion();
    private static native void   jsvmDiagnostics();

    private static native String getBindingsVersion();
    private static native void   bindingsDiagnostics();

    private static native String getCocosVersion();
    private static native void   cocosDiagnostics();
}
