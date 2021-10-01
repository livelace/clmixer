libraries {
    appimage {
        source = "clmixer"
        destination = 'clmixer-${VERSION}.appimage'
    }
    cmake
    git {
        repo_url = "https://github.com/livelace/clmixer.git"
    }
    harbor_replicate {
        policy = "clmixer"
    }
    k8s_build {
        image = "harbor-core.k8s-2.livelace.ru/dev/gobuild:latest"
        privileged = true
    }
    kaniko {
        destination = "data/clmixer:latest"
    }
    mattermost
    nexus {
        source = 'clmixer-${VERSION}.appimage'
        destination = 'dists-internal/clmixer/clmixer-${VERSION}.appimage'
    }
    sonarqube
    version
}
