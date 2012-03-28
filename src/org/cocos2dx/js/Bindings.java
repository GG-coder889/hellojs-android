package org.cocos2dx.js;

import android.content.res.AssetManager;
import android.util.Log;

public class Bindings {
    static private final String LOGTAG = "org.spidermonkey.Bindings";

    public static StringBuilder getLibVersions() {
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

    public static void executeJS(AssetManager assetmanager,
                                 String relativePath) {
        Log.d(LOGTAG, "executeJS assets/" + relativePath);

        runJSFromAssets(assetmanager, relativePath);
    }

    private static native String getJSVMVersion();
    private static native void   jsvmDiagnostics();
    private static native void   runJSFromAssets(AssetManager a,
                                                 String s);

    private static native String getBindingsVersion();
    private static native void   bindingsDiagnostics();

    private static native String getCocosVersion();
    private static native void   cocosDiagnostics();
}
