libraries {
    appimage {
        source = "clmixer"
        destination = "clmixer.appimage"
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
        destination = "data/clmixer:latest"
    }
    mattermost
    nexus {
        source = "clmixer.appimage"
        destination = "dists-internal/clmixer/clmixer.appimage"
    }
    sonarqube

}
