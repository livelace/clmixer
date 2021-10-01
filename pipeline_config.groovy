libraries {
    appimage {
        source = "clmixer"
        destination = "clmixer-v1.1.0.appimage"
    }
    cmake
    git {
        repo_url = "https://github.com/livelace/clmixer.git"
    }
    harbor_replicate {
        policy = "clmixer"
    }
    k8s_build {
        image = "harbor-core.k8s-2.livelace.ru/dev/clmixer:latest"
        privileged = true
    }
    kaniko {
        destination = "data/clmixer:v1.1.0"
    }
    mattermost
    nexus {
        source = "clmixer-v1.1.0.appimage"
        destination = "dists-internal/clmixer/clmixer-v1.1.0.appimage"
    }
    sonarqube

}
