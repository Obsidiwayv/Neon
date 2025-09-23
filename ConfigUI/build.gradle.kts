plugins {
    id("java")
}

group = "space.wayvlyte.neon"
version = "1.0"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")

    implementation("com.google.code.gson:gson:2.7")
}

tasks.withType<Jar>() {
    manifest {
        attributes["Main-Class"] = "space.wayvlyte.neon.Application"
    }
    val deps = configurations.runtimeClasspath
        .get()
        .map(::zipTree)
    from(deps)
    duplicatesStrategy = DuplicatesStrategy.EXCLUDE
}

tasks.test {
    useJUnitPlatform()
}