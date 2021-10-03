def APP_NAME = "clmixer"
def APP_REPO = "https://github.com/livelace/clmixer.git"
def APP_VERSION = env.VERSION + '-${GIT_COMMIT_SHORT}'
def IMAGE_TAG = env.VERSION == "master" ? "latest" : env.VERSION

libraries {
    appimage {
        source = "${APP_NAME}"
        destination = "${APP_NAME}-${APP_VERSION}.appimage"
    }
    cmake
    git {
        repo_url = "${APP_REPO}"
        repo_branch = env.VERSION
    }
    harbor_replicate {
        policy = "${APP_NAME}"
    }
    k8s_build {
        image = "harbor-core.k8s-2.livelace.ru/dev/clmixer:${IMAGE_TAG}"
        privileged = true
    }
    kaniko {
        destination = "data/${APP_NAME}:${IMAGE_TAG}"
        options = "--build-arg=IMAGE_TAG=${IMAGE_TAG}"
    }
    mattermost
    nexus {
        source = "${APP_NAME}-${APP_VERSION}.appimage"
        destination = "dists-internal/${APP_NAME}/${APP_NAME}-${APP_VERSION}.appimage"
    }
    sonarqube

}
