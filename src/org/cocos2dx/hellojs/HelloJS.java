package org.cocos2dx.hellojs;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.IOException;

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
        addScriptList(linearlayout);
    }

    static {
        System.loadLibrary("game");
    }

    private void addVersionStringsToLinearLayout(LinearLayout linearlayout) {
        TextView tv = new TextView(this);
        tv.setText(getLibVersions());
        linearlayout.addView(tv);
    }

    private void addScriptList(LinearLayout linearlayout) {
        try {
            String[] scripts = getJSAssets();

            Log.d(LOGTAG, "Scripts :\n --- js/\n      |");
            for (String s: scripts) {
                Log.d(LOGTAG, "      +-- " + s);
            }

        } catch (java.io.IOException ioe) {
            Log.d(LOGTAG, "Exception reading scripts from assets/js.\n" + ioe);
            return;
        }
    }

    private String[] getJSAssets() throws java.io.IOException {
        AssetManager assets = getAssets();
        String[] assetList = assets.list("js");
        return assetList;
    }

    private StringBuilder getLibVersions() {
        StringBuilder content = new StringBuilder();
        content.append("Hello Cocos, JS, Android!\n\n");
        try {
            content.append("Cocos2d Version = " + getCocosVersion() + "\n");
        } catch (Throwable t) {
            Log.d(LOGTAG, "Exception : " + t);
            content.append("Error in Cocos2d.\n");
        }

        try {
        content.append("JS VM Version = " + getJSVMVersion() + "\n");
        } catch (Throwable t) {
            Log.d(LOGTAG, "Exception : " + t);
            content.append("Error in JavaScript VM.\n");
        }

        try {
        content.append("Bindings Version = " + getBindingsVersion() + "\n");
        } catch (Throwable t) {
            Log.d(LOGTAG, "Exception : " + t);
            content.append("Error in Cocos2d/JS Bindings.\n");
        }

        return content;
    }

    private static native String getJSVMVersion();
    private static native void   jsvmDiagnostics();

    private static native String getBindingsVersion();
    private static native void   bindingsDiagnostics();

    private static native String getCocosVersion();
    private static native void   cocosDiagnostics();
}
