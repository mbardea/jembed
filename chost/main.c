#include <stdio.h>
#include <jni.h>

JNIEnv* create_vm() {
    JavaVM* jvm;
    JNIEnv* env;
    JavaVMInitArgs args;
    JavaVMOption options[1];
    
    /* There is a new JNI_VERSION_1_4, but it doesn't add anything for the purposes of our example. */
    args.version = JNI_VERSION_1_2;
    args.nOptions = 1;
    options[0].optionString = "-Djava.class.path=../java/target/malt-parser-1.0.jar";
    args.options = options;
    args.ignoreUnrecognized = JNI_FALSE;

    JNI_CreateJavaVM(&jvm, (void **)&env, &args);
    return env;
}

void invoke_class(JNIEnv* env) {
    jclass parserClass;
    jmethodID parseMethod;
    jstring parseArg;

    parserClass = (*env)->FindClass(env, "com/sdl/malt/parser/Parser");
    if (!parserClass) {
        printf("Cannot find parser class\n");
        return;
    }

    parseMethod = (*env)->GetStaticMethodID(env, parserClass, "parse", "(Ljava/lang/String;)Ljava/lang/String;");
    if (!parseMethod) {
        printf("Cannot find parser method\n");
        return;
    }

    int i;
    for(i = 0; i < 10; i++) {
        parseArg = (*env)->NewStringUTF(env, "This is the sentence to parse.");
        jstring resultJNIStr = (*env)->CallObjectMethod(env, parserClass, parseMethod, parseArg);
        const char *resultCStr = (*env)->GetStringUTFChars(env, resultJNIStr, NULL);
        if (NULL == resultCStr) return;
        printf("Received: %s\n", resultCStr);
        (*env)->ReleaseStringUTFChars(env, resultJNIStr, resultCStr);
    }
}


int main(int argc, char **argv) {
    JNIEnv* env = create_vm();
    invoke_class(env);
}
